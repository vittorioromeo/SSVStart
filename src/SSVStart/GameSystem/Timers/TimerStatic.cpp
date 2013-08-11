// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/Timers/TimerStatic.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
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
}
