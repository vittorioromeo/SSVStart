#ifndef SSVS_ANIMATION
#define SSVS_ANIMATION

#include <vector>
#include <string>

namespace ssvs
{
	struct AnimationStep { std::string label; float time; };

	class Animation
	{
		private:
			std::vector<AnimationStep> steps;
			int currentIndex{0};
			float speed{1}, currentTime{0};
			bool loop{true}, pingPong{false}, reverse{false};

			void nextStep();

		public:
			Animation() = default;
			void update(float mFrameTime);
			void addStep(AnimationStep mStep);
			void addSteps(std::vector<AnimationStep> mSteps);
			void addSteps(std::vector<std::string> mStepLabels, float mStepTime);

			// Getters
			const AnimationStep& getCurrentStep() const;
			const std::string& getCurrentLabel() const;

			// Setters
			void setSpeed(float mSpeed);
			void setLoop(bool mLoop);
			void setPingPong(bool mPingPong);
			void setReverse(bool mReverse);
	};
}

#endif
