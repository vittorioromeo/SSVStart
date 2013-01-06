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
#include "GameState.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	GameWindow::GameWindow(string mTitle, unsigned int mScreenWidth, unsigned int mScreenHeight, int mPixelMultiplier, bool mLimitFps, bool mFullscreen) :
			title{mTitle}, width{mScreenWidth}, height{mScreenHeight}, pixelMultiplier{mPixelMultiplier}, fullscreen{mFullscreen}
	{
		recreateWindow();

		renderWindow.setVerticalSyncEnabled(false);
		if (mLimitFps) renderWindow.setFramerateLimit(60);
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

	void GameWindow::clear(Color mColor) { renderWindow.clear(mColor); }
	void GameWindow::draw(Drawable& mDrawable) { renderWindow.draw(mDrawable); }
	void GameWindow::pollEvent(Event& mEvent) { renderWindow.pollEvent(mEvent); }

	void GameWindow::recreateWindow()
	{
		if(fullscreen) renderWindow.create({width, height}, title, Style::Fullscreen);
		else renderWindow.create({width, height}, title, Style::Default);

		renderWindow.setSize({width * pixelMultiplier, height * pixelMultiplier});
	}

	inline void GameWindow::runGame()
	{
		gamePtr->update(frameTime);
		gamePtr->draw();
	}
	inline void GameWindow::runInput()
	{
		Event event;
		renderWindow.pollEvent(event);

		if(event.type == Event::GainedFocus) hasFocus = true;
		else if(event.type == Event::LostFocus) hasFocus = false;
		else if(event.type == Event::Closed) running = false;
	}
	inline void GameWindow::runFps()
	{
		if(staticFrameTime) frameTime = staticFrameTimeValue;
		else frameTime = clock.restart().asSeconds() * 60.f;

		if (frameTime > 4) frameTime = 4;

		fps = 60.f / frameTime;
	}
} /* namespace ssvs */
