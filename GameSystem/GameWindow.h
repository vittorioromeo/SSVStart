// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <string>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace ssvs
{
	class GameState;

	class GameWindow
	{
		private:
			GameState* gamePtr{nullptr}; // not owned, just pointed to
			sf::RenderWindow renderWindow;
			sf::Clock clock;
			std::string title{""};
			
			float frameTime{0};
			float fps{0};
			bool running{true};
			bool hasFocus{true};

			unsigned int width, height;
			int pixelMultiplier;
			bool fullscreen;
			bool staticFrameTime{false};
			float staticFrameTimeValue{1};
			float frameTimeLimit{4.f};
			
			void runInput();
			void runGame();
			void runFps();

		public:
			GameWindow(std::string mTitle, unsigned int mScreenWidth = 320, unsigned int mScreenHeight = 240, int mPixelMultiplier = 1, bool mFullscreen = false);
			GameWindow(const GameWindow&) = delete; // non construction-copyable
			GameWindow& operator=(const GameWindow&) = delete; // non copyable

			// Main
			void run();
			void stop();
			void recreateWindow();

			// Drawing
			void clear(sf::Color mColor);
			void draw(const sf::Drawable& mDrawable);
			void pollEvent(sf::Event& mEvent);

			// Input
			bool isKeyPressed(sf::Keyboard::Key mKey);
			bool isButtonPressed(sf::Mouse::Button mButton);

			// Getters
			sf::RenderWindow& getRenderWindow();
			sf::Vector2f getMousePosition();
			float getFPS();
			unsigned int getWidth();
			unsigned int getHeight();
			bool getFullscreen();

			// Setters
			void setGame(GameState*);
			void setSize(unsigned int mWidth, unsigned int mHeight);
			void setFullscreen(bool mFullscreen);
			void setStaticFrameTime(bool mEnabled);
			void setVsync(bool mEnabled);
			void setMouseCursorVisible(bool mEnabled);
			void setStaticFrameTimeValue(float mValue);
			void setTitle(const std::string& mTitle);
			void setFPSLimit(float mFPSLimit);
	};
} /* namespace ssvs */
#endif /* GAMEWINDOW_H_ */
