// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "GameWindow.h"
#include "GameState.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	GameWindow::GameWindow(string mTitle, unsigned int mScreenWidth, unsigned int mScreenHeight, int mPixelMultiplier, bool mFullscreen) :
		title{mTitle}, width{mScreenWidth}, height{mScreenHeight}, pixelMultiplier{mPixelMultiplier}, fullscreen{mFullscreen}
	{
		recreateWindow();
	}

	void GameWindow::run()
	{
		while(running)
		{
			renderWindow.setActive(true);
			renderWindow.clear();
			runInput(); runGame();
			renderWindow.display();
			runFps();
		}
	}
	void GameWindow::stop() { running = false; }

	void GameWindow::clear(Color mColor) { renderWindow.clear(mColor); }
	void GameWindow::draw(const Drawable& mDrawable) { renderWindow.draw(mDrawable); }
	void GameWindow::pollEvent(Event& mEvent) { renderWindow.pollEvent(mEvent); }

	void GameWindow::recreateWindow()
	{
		if(renderWindow.isOpen()) renderWindow.close();
		if(fullscreen) renderWindow.create({width, height}, title, Style::Fullscreen);
		else renderWindow.create({width, height}, title, Style::Default);
		renderWindow.setSize({width * pixelMultiplier, height * pixelMultiplier});
	}

	void GameWindow::runGame() { gamePtr->update(frameTime); gamePtr->draw(); }
	void GameWindow::runInput()
	{
		Event event; renderWindow.pollEvent(event);

		if(event.type == Event::GainedFocus) hasFocus = true;
		else if(event.type == Event::LostFocus) hasFocus = false;
		else if(event.type == Event::Closed) running = false;
	}
	void GameWindow::runFps()
	{
		if(staticFrameTime) frameTime = staticFrameTimeValue;
		else
		{
			frameTime = clock.restart().asSeconds() * 60.f;
			if(frameTime > frameTimeLimit) frameTime = frameTimeLimit;
		}

		fps = 60.f / frameTime;		
	}

	bool GameWindow::isKeyPressed(Keyboard::Key mKey) 		{ return hasFocus && Keyboard::isKeyPressed(mKey); }
	bool GameWindow::isButtonPressed(Mouse::Button mButton) { return hasFocus && Mouse::isButtonPressed(mButton); }
} /* namespace ssvs */
