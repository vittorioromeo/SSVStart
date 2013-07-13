// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ANIMATION
#define SSVS_ANIMATION

#include <vector>
#include <string>
#include <SFML/System.hpp>
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

			void nextStep();

		public:
			Animation() = default;
			void update(float mFrameTime);
			void addStep(const AnimationStep& mStep);
			void addSteps(const std::vector<AnimationStep>& mSteps);
			void addSteps(const std::vector<Vec2u>& mIndexes, float mStepTime);

			// Getters
			inline const AnimationStep& getCurrentStep() const	{ return steps[currentIndex]; }
			inline Vec2u getCurrentIndex() const				{ return getCurrentStep().index; }

			// Setters
			inline void setSpeed(float mSpeed)		{ speed = mSpeed; }
			inline void setLoop(bool mLoop)			{ loop = mLoop; }
			inline void setPingPong(bool mPingPong)	{ pingPong = mPingPong; }
			inline void setReverse(bool mReverse)	{ reverse = mReverse; }
	};
}

#endif
