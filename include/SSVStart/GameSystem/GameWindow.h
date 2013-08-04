// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMEWINDOW
#define SSVS_GAMESYSTEM_GAMEWINDOW

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class GameState;
	class TimerBase;
	class StaticTimer;
	class DynamicTimer;

	class GameWindow
	{
		friend class TimerBase;
		friend class StaticTimer;
		friend class DynamicTimer;

		private:
			GameState* gameState{nullptr}; // not owned, just pointed to
			sf::RenderWindow renderWindow;
			std::string title;
			sf::Clock clock;

			bool running{true}, focus{true}, mustRecreate{true}, vsync{false};

			unsigned int width, height, antialiasingLevel{3};
			int pixelMultiplier;
			bool fullscreen;

			Uptr<TimerBase> timer;

			void runInput();
			void runUpdate(float mFrameTime);
			void runDraw();

		public:
			GameWindow(const std::string& mTitle, TimerBase& mTimer, unsigned int mScreenWidth = 320, unsigned int mScreenHeight = 240, int mPixelMultiplier = 1, bool mFullscreen = false);
			GameWindow(const GameWindow&) = delete; // non construction-copyable
			GameWindow& operator=(const GameWindow&) = delete; // non copyable

			void run();
			inline void stop() { running = false; }
			void recreateWindow();

			inline void clear(const sf::Color& mColor) { renderWindow.clear(mColor); }
			inline void draw(const sf::Drawable& mDrawable, const sf::RenderStates& mStates = sf::RenderStates::Default) { renderWindow.draw(mDrawable, mStates); }

			inline bool isMouseInside() const
			{
				const auto& pos(sf::Mouse::getPosition(renderWindow));
				const auto& windowSize(Vec2i(renderWindow.getSize()));
				return pos.x > 0 && pos.y > 0 && pos.x < windowSize.x && pos.y < windowSize.y;
			}

			inline bool isKeyPressed(sf::Keyboard::Key mKey) const				{ return focus && sf::Keyboard::isKeyPressed(mKey); }
			inline bool isButtonPressed(sf::Mouse::Button mButton) const		{ return focus && sf::Mouse::isButtonPressed(mButton) && isMouseInside(); }

			// Setters
			inline void setFullscreen(bool mFullscreen) 						{ fullscreen = mFullscreen; mustRecreate = true; }
			inline void setSize(unsigned int mWidth, unsigned int mHeight)		{ width = mWidth; height = mHeight; mustRecreate = true; }
			inline void setAntialiasingLevel(unsigned int mAntialiasingLevel)	{ antialiasingLevel = mAntialiasingLevel; mustRecreate = true; }
			inline void setVsync(bool mEnabled)									{ vsync = mEnabled; mustRecreate = true;  }
			inline void setMouseCursorVisible(bool mEnabled) 					{ renderWindow.setMouseCursorVisible(mEnabled); }
			inline void setTitle(const std::string& mTitle)						{ title = mTitle; renderWindow.setTitle(mTitle); }
			inline void setFPSLimit(float mFPSLimit)							{ renderWindow.setFramerateLimit(mFPSLimit); }
			void setGameState(GameState& mGameState);

			// Getters
			inline sf::RenderWindow& getRenderWindow()			{ return renderWindow; }
			inline bool getFullscreen() const					{ return fullscreen; }
			inline unsigned int getWidth() const				{ return width; }
			inline unsigned int getHeight() const				{ return height; }
			inline unsigned int getAntialiasingLevel() const	{ return antialiasingLevel; }
			inline Vec2f getMousePosition() const				{ return renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow)); }
			inline bool hasFocus() const						{ return focus; }
			inline bool getVsync() const						{ return vsync; }
			float getFPS() const;

			template<typename T> inline T& getTimer() { return static_cast<T&>(*timer); }
	};
}

#endif
