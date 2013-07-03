// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ANIMATION
#define SSVS_ANIMATION

#include <vector>
#include <string>
#include <SFML/System.hpp>

namespace ssvs
{
	struct AnimationStep { sf::Vector2u index; float time; };

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
			void addStep(const AnimationStep& mStep);
			void addSteps(const std::vector<AnimationStep>& mSteps);
			void addSteps(const std::vector<sf::Vector2u>& mIndexes, float mStepTime);

			// Getters
			const AnimationStep& getCurrentStep() const;
			sf::Vector2u getCurrentIndex() const;

			// Setters
			void setSpeed(float mSpeed);
			void setLoop(bool mLoop);
			void setPingPong(bool mPingPong);
			void setReverse(bool mReverse);
	};
}

#endif
