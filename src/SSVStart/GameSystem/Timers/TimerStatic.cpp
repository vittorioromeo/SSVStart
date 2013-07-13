// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/Timers/TimerStatic.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	StaticTimer::StaticTimer(GameWindow& mGameWindow, float mStep, float mTimeSlice, float mMaxLoops) : TimerBase(mGameWindow), step{mStep}, timeSlice{mTimeSlice}, maxLoops{mMaxLoops} { }

	void StaticTimer::runUpdate()
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

	StaticTimer& createStaticTimer(GameWindow& mGameWindow, float mStep, float mSpeed, float mMaxLoops) { return *(new StaticTimer{mGameWindow, mStep, mSpeed, mMaxLoops}); }
}
