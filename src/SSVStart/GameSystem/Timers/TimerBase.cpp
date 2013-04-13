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
