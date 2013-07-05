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
		title{mTitle}, width{mScreenWidth}, height{mScreenHeight}, pixelMultiplier{mPixelMultiplier}, fullscreen{mFullscreen}, timer(mTimer) { recreateWindow(); }
	GameWindow::~GameWindow() { delete &timer; }

	void GameWindow::run()
	{
		while(running)
		{
			if(mustRecreate) recreateWindow();

			renderWindow.setActive(true);
			renderWindow.clear();

			gamePtr->refreshInput();
			runInput();
			timer.runUpdate();
			gamePtr->onPostUpdate();

			timer.runDraw();
			renderWindow.display();

			timer.runFrameTime();
			timer.runFps();
		}
	}
	void GameWindow::stop() { running = false; }

	void GameWindow::clear(Color mColor) { renderWindow.clear(mColor); }
	void GameWindow::draw(const Drawable& mDrawable, const RenderStates& mStates) { renderWindow.draw(mDrawable, mStates); }
	void GameWindow::pollEvent(Event& mEvent) { renderWindow.pollEvent(mEvent); }

	void GameWindow::recreateWindow()
	{
		ContextSettings contextSettings{0, 0, antialiasingLevel, 0, 0};
		unsigned int multipliedWidth{width * pixelMultiplier}, multipliedHeight{height * pixelMultiplier};

		if(renderWindow.isOpen()) renderWindow.close();
		if(fullscreen) renderWindow.create({width, height}, title, Style::Fullscreen, contextSettings);
		else
		{
			auto desktopMode(VideoMode::getDesktopMode());
			renderWindow.create({width, height}, title, Style::Default, contextSettings);
			renderWindow.setPosition(Vector2i(desktopMode.width / 2 - multipliedWidth / 2, desktopMode.height / 2 - multipliedHeight / 2));
		}
		renderWindow.setSize({multipliedWidth, multipliedHeight});

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

			gamePtr->handleEvent(event);
		}

		gamePtr->updateInput(timer.getFrameTime());
	}
	void GameWindow::runUpdate(float mFrameTime) { gamePtr->update(mFrameTime); }
	void GameWindow::runDraw() { gamePtr->draw(); }

	bool GameWindow::isKeyPressed(Keyboard::Key mKey)		{ return focus && Keyboard::isKeyPressed(mKey); }
	bool GameWindow::isButtonPressed(Mouse::Button mButton)	{ return focus && Mouse::isButtonPressed(mButton); }
}
