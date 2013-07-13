// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/GameWindow.h"
#include "SSVStart/GameSystem/GameState.h"
#include "SSVStart/GameSystem/Timers/TimerBase.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	GameWindow::GameWindow(const string& mTitle, TimerBase& mTimer, unsigned int mScreenWidth, unsigned int mScreenHeight, int mPixelMultiplier, bool mFullscreen) :
		title{mTitle}, width{mScreenWidth}, height{mScreenHeight}, pixelMultiplier{mPixelMultiplier}, fullscreen{mFullscreen}, timer(&mTimer) { }

	void GameWindow::run()
	{
		while(running)
		{
			if(mustRecreate) recreateWindow();

			renderWindow.setActive(true);
			renderWindow.clear();

			gameState->refreshInput();
			runInput();
			timer->runUpdate();
			gameState->onPostUpdate();

			timer->runDraw();
			renderWindow.display();

			timer->runFrameTime();
			timer->runFps();
		}
	}

	void GameWindow::recreateWindow()
	{
		if(renderWindow.isOpen()) renderWindow.close();
		renderWindow.create({width, height}, title, fullscreen ? Style::Fullscreen : Style::Default, ContextSettings{0, 0, antialiasingLevel, 0, 0});
		renderWindow.setSize({width * pixelMultiplier, height * pixelMultiplier});
		mustRecreate = false;
	}

	void GameWindow::runInput()
	{
		Event event;
		while(renderWindow.pollEvent(event))
		{
			switch(event.type)
			{
				case Event::Closed: running = false; break;
				case Event::GainedFocus: focus = true; break;
				case Event::LostFocus: focus = false; break;
				default: break;
			}

			gameState->handleEvent(event);
		}

		gameState->updateInput(timer->getFrameTime());
	}
	void GameWindow::runUpdate(float mFrameTime)	{ gameState->update(mFrameTime); }
	void GameWindow::runDraw()						{ gameState->draw(); }

	void GameWindow::setGameState(GameState& mGameState)	{ gameState = &mGameState; mGameState.gameWindowPtr = this; }
	float GameWindow::getFPS() const						{ return timer->getFps(); }
}
