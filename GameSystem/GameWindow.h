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

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <string>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


namespace ssvs
{
	class Game;
	
	class GameWindow
	{
		private:
			Game* gamePtr{nullptr}; // not owned, just pointed to
			sf::RenderWindow renderWindow;
			sf::Clock clock;
			std::string title{""};
			unsigned int width, height;
			int pixelMultiplier;
			bool fullscreen;
			bool staticFrameTime{false};
			float staticFrameTimeValue{1};
			float frameTime{0};
			float fps{0};
			bool running{true};
			bool hasFocus{true};
			
			GameWindow(const GameWindow&); // non construction-copyable
			GameWindow& operator=(const GameWindow&); // non copyable
			
			inline void runInput();
			inline void runGame();
			inline void runFps();

		public:
			GameWindow(std::string mTitle, unsigned int mScreenWidth = 320, unsigned int mScreenHeight = 240, int mPixelMultiplier = 1, bool mLimitFps = false, bool mFullscreen = false);

			void run();
			void stop();
			void recreateWindow();
			void clear(sf::Color mColor);
			void draw(sf::Drawable& mDrawable);
			void pollEvent(sf::Event& mEvent);

			// Properties
			sf::RenderWindow& getRenderWindow();
			bool isKeyPressed(sf::Keyboard::Key mKey);
			float getFps();
			unsigned int getWidth();
			unsigned int getHeight();
			bool getFullscreen();
			void setGame(Game*);
			void setSize(unsigned int mWidth, unsigned int mHeight);
			void setFullscreen(bool mFullscreen);
			void setStaticFrameTime(bool mEnabled);
			void setVsync(bool mEnabled);
			void setMouseCursorVisible(bool mEnabled);
			void setStaticFrameTimeValue(float mValue);
			void setTitle(std::string mTitle);
	};
} /* namespace ssvs */
#endif /* GAMEWINDOW_H_ */
