/* The MIT License (MIT)
 * Copyright (c) 2012 Vittorio Romeo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "GameWindow.h"
#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "../Utils.h"

namespace ssvs
{
	GameWindow::GameWindow(string mTitle, unsigned int mScreenWidth, unsigned int mScreenHeight, int mPixelMultiplier, bool mLimitFps, bool mFullscreen) :
			title{mTitle}, width{mScreenWidth}, height{mScreenHeight}, pixelMultiplier{mPixelMultiplier}, isFullscreen{mFullscreen}
	{
		recreateWindow();

		renderWindow.setVerticalSyncEnabled(false);
		if (mLimitFps) renderWindow.setFramerateLimit(60);		
	}

	void GameWindow::setGame(Game* mGamePtr)
	{
		gamePtr = mGamePtr;
		mGamePtr->gameWindowPtr = this;
	}
	void GameWindow::run()
	{
		while (running)
		{
			renderWindow.setActive(true);
			renderWindow.clear();
			
			runInput();
			runGame();
			
			renderWindow.display();
			
			runFps();
		}
	}
	void GameWindow::stop() { running = false; }
	float GameWindow::getFps() { return fps; }
	
	inline void GameWindow::runGame()
	{
		gamePtr->update(frameTime);
		gamePtr->draw();
	}
	inline void GameWindow::runInput()
	{
		sf::Event event;
		renderWindow.pollEvent(event);

		if(event.type == sf::Event::GainedFocus) hasFocus = true;
		if(event.type == sf::Event::LostFocus) hasFocus = false;

		if(event.type == sf::Event::Closed) running = false; // DEBUG
	}
	inline void GameWindow::runFps()
	{
		if(isFrameTimeStatic) frameTime = staticFrameTime;
		else frameTime = clock.restart().asSeconds() * 60.f;
		
		fps = 60.f / frameTime;
	}

	bool GameWindow::isKeyPressed(Keyboard::Key mKey)
	{
		return hasFocus && Keyboard::isKeyPressed(mKey);
	}
	bool GameWindow::getFullscreen() { return isFullscreen; }
	void GameWindow::setFullscreen(bool mFullscreen)
	{
		isFullscreen = mFullscreen;

		renderWindow.close();
		recreateWindow();
	}
	void GameWindow::recreateWindow()
	{
		if(isFullscreen) renderWindow.create(VideoMode{width, height}, title, Style::Fullscreen);
		else renderWindow.create(VideoMode{width, height}, title, Style::Default);

		renderWindow.setSize(Vector2u(width * pixelMultiplier, height * pixelMultiplier));
	}

	void GameWindow::setSize(unsigned int mWidth, unsigned int mHeight)
	{
		width = mWidth;
		height = mHeight;

		renderWindow.close();
		recreateWindow();
	}
	unsigned int GameWindow::getWidth() { return width; }
	unsigned int GameWindow::getHeight() { return height; }
} /* namespace ssvs */
