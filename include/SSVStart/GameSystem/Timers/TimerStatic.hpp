// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_STATIC
#define SSVS_GAMESYSTEM_TIMERS_STATIC

#include "SSVStart/GameSystem/Timers/TimerBase.hpp"
#include "SSVStart/GameSystem/GameWindow.hpp"

namespace ssvs
{
	class TimerStatic final : public TimerBase
	{
		private:
			FT step, timeSlice, time{0};
			float maxLoops, loops{0};

		public:
			TimerStatic(GameEngine& mGameEngine, FT mStep = 1.f, FT mTimeSlice = 1.f, float mMaxLoops = 50.f) noexcept
				: TimerBase(mGameEngine), step{mStep}, timeSlice{mTimeSlice}, maxLoops{mMaxLoops} { }

			inline void runUpdate() override
			{
				loops = 0;
				time += frameTime;

				while(time >= timeSlice && loops < maxLoops)
				{
					gameEngine.updateFromTimer(step);
					time -= timeSlice;
					++loops;
				}
			}

			inline void setStep(FT mStep) noexcept				{ step = mStep; }
			inline void setTimeSlice(FT mTimeSlice) noexcept	{ timeSlice = mTimeSlice; }
			inline void setMaxLoops(float mMaxLoops) noexcept	{ maxLoops = mMaxLoops; }

			inline FT getStep() const noexcept			{ return step; }
			inline FT getTimeSlice() const noexcept		{ return timeSlice; }
			inline FT getTime() const noexcept			{ return time; }
			inline float getMaxLoops() const noexcept	{ return maxLoops; }
			inline float getLoops() const noexcept		{ return loops; }
	};
}

#endif
