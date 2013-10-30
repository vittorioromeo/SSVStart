// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_STATIC
#define SSVS_GAMESYSTEM_TIMERS_STATIC

#include "SSVStart/GameSystem/Timers/TimerBase.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	class GameWindow;

	class TimerStatic final : public TimerBase
	{
		private:
			float step, timeSlice, maxLoops, time{0}, loops{0};

		public:
			TimerStatic(GameWindow& mGameWindow, float mStep = 1.f, float mTimeSlice = 1.f, float mMaxLoops = 50) : TimerBase(mGameWindow), step{mStep}, timeSlice{mTimeSlice}, maxLoops{mMaxLoops} { }

			inline void runUpdate() override
			{
				loops = 0;
				time += frameTime;
				while(time >= timeSlice && loops < maxLoops)
				{
					gameWindow.runUpdate(step);
					time -= timeSlice;
					++loops;
				}
			}

			inline void setStep(float mStep) noexcept			{ step = mStep; }
			inline void setTimeSlice(float mTimeSlice) noexcept	{ timeSlice = mTimeSlice; }
			inline void setMaxLoops(float mMaxLoops) noexcept	{ maxLoops = mMaxLoops; }

			inline float getStep() const noexcept		{ return step; }
			inline float getTimeSlice() const noexcept	{ return timeSlice; }
			inline float getMaxLoops() const noexcept	{ return maxLoops; }
			inline float getTime() const noexcept		{ return time; }
			inline float getLoops() const noexcept		{ return loops; }
	};
}

#endif
