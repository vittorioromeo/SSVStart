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
			bool reverse{false};
			Type type;

			void nextStep()
			{
				assert(index >= 0 && index < steps.size());

				time = 0;

				if(!reverse)
				{
					if(index < steps.size() - 1) { ++index; return; }

					switch(type)
					{
						case Type::Once: return;
						case Type::Loop: index = 0; return;
						case Type::PingPong: reverse = true; --index; return;
					}
				}
				else
				{
					if(index > 0) { --index; return; }

					switch(type)
					{
						case Type::Once: return;
						case Type::Loop: index = steps.size() - 1; return;
						case Type::PingPong: reverse = false; ++index; return;
					}

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
			inline void addStep(AnimationStep mStep)											{ steps.emplace_back(std::move(mStep)); }
			inline void addSteps(const std::initializer_list<AnimationStep>& mSteps)			{ for(const auto& s : mSteps) steps.push_back(s); }
			inline void addSteps(const std::initializer_list<Vec2u>& mIndexes, float mStepTime)	{ for(const auto& i : mIndexes) steps.push_back({i, mStepTime}); }

			inline void setSpeed(float mSpeed) noexcept		{ speed = mSpeed; }
			inline void setType(Type mType) noexcept		{ type = mType; }
			inline void setReverse(bool mReverse) noexcept	{ reverse = mReverse; }

			inline float getSpeed() const noexcept			{ return speed; }
			inline float getTime() const noexcept			{ return time; }
			inline unsigned int getIndex() const noexcept	{ return index; }
			inline bool getReverse() const noexcept			{ return reverse; }
			inline Type getType() const noexcept			{ return type; }
			inline const AnimationStep& getStep() const		{ return steps[index]; }
			inline Vec2u getTileIndex() const				{ return getStep().index; }
	};
}

#endif
