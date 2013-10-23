// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ANIMATION
#define SSVS_ANIMATION

#include <cassert>
#include <vector>
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	struct AnimationStep { Vec2u index; float time; };

	class Animation
	{
		public:
			enum class Type{Once, Loop, PingPong};

		private:
			std::vector<AnimationStep> steps;
			unsigned int index{0};
			float speed{1}, time{0};
			int dir{1};
			Type type;
			unsigned int currentTarget, nextTarget;

			inline void refreshTargets()
			{
				if(dir > 0)	{ currentTarget = steps.size() - 1;	nextTarget = 0u; }
				else		{ currentTarget = 0u;				nextTarget = steps.size() - 1; }
			}

			inline void nextStep()
			{
				assert(index >= 0 && index < steps.size());

				time = 0;

				if(dir > 0 ? index < currentTarget : index > 0u) { index += dir; return; }

				switch(type)
				{
					case Type::Once: return;
					case Type::Loop: index = nextTarget; return;
					case Type::PingPong: dir *= -1; refreshTargets(); index += dir; return;
				}
			}

		public:
			Animation(Type mType = Type::Loop) noexcept : type{mType} { }
			inline void update(float mFT)
			{
				if(steps.empty()) return;

				time += mFT * speed;
				if(time >= getStep().time) nextStep();
			}
			inline void addStep(AnimationStep mStep)											{ steps.emplace_back(std::move(mStep)); refreshTargets(); }
			inline void addSteps(const std::initializer_list<AnimationStep>& mSteps)			{ for(const auto& s : mSteps) addStep(s); }
			inline void addSteps(const std::initializer_list<Vec2u>& mIndexes, float mStepTime)	{ for(const auto& i : mIndexes) addStep({i, mStepTime}); }

			inline void setSpeed(float mSpeed) noexcept		{ speed = mSpeed; }
			inline void setType(Type mType) noexcept		{ type = mType; }
			inline void setReverse(bool mReverse) noexcept	{ dir = mReverse ? -1 : 1; refreshTargets(); }

			inline float getSpeed() const noexcept			{ return speed; }
			inline float getTime() const noexcept			{ return time; }
			inline unsigned int getIdx() const noexcept		{ return index; }
			inline bool getReverse() const noexcept			{ return dir == -1; }
			inline Type getType() const noexcept			{ return type; }
			inline const AnimationStep& getStep() const		{ return steps[index]; }
			inline Vec2u getTileIndex() const				{ return getStep().index; }
	};
}

#endif
