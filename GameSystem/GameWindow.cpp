// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "GameWindow.h"
#include "GameState.h"
#include "Timers.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	GameWindow::GameWindow(string mTitle, unsigned int mScreenWidth, unsigned int mScreenHeight, int mPixelMultiplier, bool mFullscreen) :
		title{mTitle}, width{mScreenWidth}, height{mScreenHeight}, pixelMultiplier{mPixelMultiplier}, fullscreen{mFullscreen}, timer{new DynamicTimer{*this}}
	{
		recreateWindow();
	}

	void GameWindow::run()
	{
		while(running)
		{
			renderWindow.setActive(true);
			renderWindow.clear();
			runInput();
			timer->runUpdate();
			timer->runDraw();
			renderWindow.display();
			timer->runFrameTime();
			timer->runFps();
		}
	}
	void GameWindow::stop() { running = false; }

	void GameWindow::clear(Color mColor) { renderWindow.clear(mColor); }
	void GameWindow::draw(const Drawable& mDrawable) { renderWindow.draw(mDrawable); }
	void GameWindow::pollEvent(Event& mEvent) { renderWindow.pollEvent(mEvent); }

	void GameWindow::recreateWindow()
	{
		ContextSettings contextSettings{0, 0, antialiasingLevel, 0, 0};

		if(renderWindow.isOpen()) renderWindow.close();
		if(fullscreen) renderWindow.create({width, height}, title, Style::Fullscreen, contextSettings);
		else renderWindow.create({width, height}, title, Style::Default, contextSettings);
		renderWindow.setSize({width * pixelMultiplier, height * pixelMultiplier});
	}

	void GameWindow::runInput()
	{
		Event event; renderWindow.pollEvent(event);
		gamePtr->updateInput(timer->getFrameTime());

		if(event.type == Event::GainedFocus) focus = true;
		else if(event.type == Event::LostFocus) focus = false;
		else if(event.type == Event::Closed) running = false;
	}
	void GameWindow::runUpdate() { gamePtr->update(timer->getFrameTime()); }
	void GameWindow::runDraw() { gamePtr->draw(); }	
	void GameWindow::runFps() { }

	bool GameWindow::isKeyPressed(Keyboard::Key mKey) 		{ return focus && Keyboard::isKeyPressed(mKey); }
	bool GameWindow::isButtonPressed(Mouse::Button mButton) { return focus && Mouse::isButtonPressed(mButton); }
}
