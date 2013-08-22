// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ANIMATION
#define SSVS_ANIMATION

#include <vector>
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	struct AnimationStep { Vec2u index; float time; };

	class Animation
	{
		private:
			std::vector<AnimationStep> steps;
			int currentIndex{0};
			float speed{1}, currentTime{0};
			bool loop{true}, pingPong{false}, reverse{false};

			void nextStep()
			{
				int lastIndex{currentIndex};
				reverse ? --currentIndex : ++currentIndex;

				if(currentIndex >= static_cast<int>(steps.size()))
				{
					if(loop)
					{
						if(pingPong) { reverse = !reverse; currentIndex = lastIndex; }
						else currentIndex = 0;
					}
					else currentIndex = lastIndex;
				}
				else if(currentIndex < 0)
				{
					if(loop)
					{
						if(pingPong) { reverse = !reverse; currentIndex = lastIndex; }
						else currentIndex = steps.size() - 1;
					}
					else currentIndex = lastIndex;
				}

				currentTime = 0;
			}

		public:
			Animation() = default;
			inline void update(float mFrameTime)
			{
				if(steps.empty()) return;

				currentTime += mFrameTime * speed;
				if(currentTime >= getCurrentStep().time) nextStep();
			}
			inline void addStep(const AnimationStep& mStep)								{ steps.push_back(mStep); }
			inline void addSteps(const std::vector<AnimationStep>& mSteps)				{ for(const auto& s : mSteps) steps.push_back(s); }
			inline void addSteps(const std::vector<Vec2u>& mIndexes, float mStepTime)	{ for(const auto& i : mIndexes) steps.push_back({i, mStepTime}); }

			inline void setSpeed(float mSpeed)		{ speed = mSpeed; }
			inline void setLoop(bool mLoop)			{ loop = mLoop; }
			inline void setPingPong(bool mPingPong)	{ pingPong = mPingPong; }
			inline void setReverse(bool mReverse)	{ reverse = mReverse; }

			inline const AnimationStep& getCurrentStep() const	{ return steps[currentIndex]; }
			inline Vec2u getCurrentIndex() const				{ return getCurrentStep().index; }
	};
}

#endif
