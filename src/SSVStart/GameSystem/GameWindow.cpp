// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/GameWindow.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	void GameWindow::run()
	{
		while(running)
		{
			if(mustRecreate) recreateWindow();

			renderWindow.setActive(true);
			renderWindow.clear();

			gameState->refreshInput();

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
		renderWindow.setSize({width * pixelMult, height * pixelMult});
		renderWindow.setVerticalSyncEnabled(vsync);
		if(replacementTimer != nullptr) { timer.reset(replacementTimer); replacementTimer = nullptr; }
		mustRecreate = false; onRecreation();
	}

	void GameWindow::runUpdate(float mFrameTime)
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
		gameState->update(mFrameTime);
	}
}
