// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/Timers/TimerDynamic.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	DynamicTimer::DynamicTimer(GameWindow& mGameWindow) : TimerBase(mGameWindow) { }

	void DynamicTimer::runUpdate() { gameWindow.runUpdate(frameTime); }
	void DynamicTimer::runFps()
	{
		if(frameTime > frameTimeLimit) frameTime = frameTimeLimit;
		TimerBase::runFps();
	}

	DynamicTimer& createDynamicTimer(GameWindow& mGameWindow) { return *(new DynamicTimer{mGameWindow}); }
}
