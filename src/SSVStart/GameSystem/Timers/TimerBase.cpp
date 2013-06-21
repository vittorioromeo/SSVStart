// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/Timers/TimerBase.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	TimerBase::TimerBase(GameWindow& mGameWindow) : gameWindow(mGameWindow) { }
	TimerBase::~TimerBase() { }

	void TimerBase::runUpdate()		{ }
	void TimerBase::runDraw()		{ gameWindow.runDraw(); }
	void TimerBase::runFrameTime()	{ frameTime = clock.restart().asSeconds() * 60.f; }
	void TimerBase::runFps()		{ fps = 60.f / frameTime; }

	float TimerBase::getFrameTime() const 	{ return frameTime; }
	float TimerBase::getFps() const 		{ return fps; }
}
