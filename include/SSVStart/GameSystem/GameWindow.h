// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMEWINDOW
#define SSVS_GAMESYSTEM_GAMEWINDOW

#include <cassert>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Global/Typedefs.h"
#include "SSVStart/GameSystem/GameState.h"
#include "SSVStart/GameSystem/Timers/TimerBase.h"

namespace ssvs
{
	class GameState;

	class GameWindow
	{
		friend class TimerBase;
		friend class StaticTimer;
		friend class DynamicTimer;

		private:
			GameState* gameState{nullptr};
			sf::RenderWindow renderWindow;
			std::string title;

			bool running{true}, focus{true}, mustRecreate{true}, vsync{false}, fullscreen{false}, fpsLimited{false};
			unsigned int width{640}, height{480}, antialiasingLevel{3}, pixelMult{1};
			float maxFPS{60.f};

			Uptr<TimerBase> timer;
			TimerBase* replacementTimer{nullptr};

			void runUpdate(float mFrameTime)
			{
				sf::Event event;
				while(renderWindow.pollEvent(event))
				{
					switch(event.type)
					{
						case sf::Event::Closed: running = false; break;
						case sf::Event::GainedFocus: focus = true; break;
						case sf::Event::LostFocus: focus = false; break;
						default: break;
					}

					gameState->handleEvent(event);
				}

				gameState->updateInput(mFrameTime);
				gameState->update(mFrameTime);
			}
			inline void runDraw() { gameState->draw(); }

		public:
			ssvu::Delegate<void()> onRecreation;

			GameWindow() = default;
			GameWindow(const GameWindow&) = delete; // non construction-copyable
			GameWindow& operator=(const GameWindow&) = delete; // non copyable

			void run()
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
			inline void stop() { running = false; }
			void recreateWindow()
			{
				if(renderWindow.isOpen()) renderWindow.close();
				renderWindow.create({width, height}, title, fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings{0, 0, antialiasingLevel, 0, 0});
				renderWindow.setSize({width * pixelMult, height * pixelMult});
				renderWindow.setVerticalSyncEnabled(vsync);
				if(replacementTimer != nullptr) { timer.reset(replacementTimer); replacementTimer = nullptr; }
				mustRecreate = false; onRecreation();
			}

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

			inline void setFullscreen(bool mFullscreen) 						{ fullscreen = mFullscreen; mustRecreate = true; }
			inline void setSize(unsigned int mWidth, unsigned int mHeight)		{ width = mWidth; height = mHeight; mustRecreate = true; }
			inline void setAntialiasingLevel(unsigned int mAntialiasingLevel)	{ antialiasingLevel = mAntialiasingLevel; mustRecreate = true; }
			inline void setVsync(bool mEnabled)									{ vsync = mEnabled; mustRecreate = true;  }
			inline void setMouseCursorVisible(bool mEnabled) 					{ renderWindow.setMouseCursorVisible(mEnabled); }
			inline void setTitle(const std::string& mTitle)						{ title = mTitle; renderWindow.setTitle(mTitle); }
			inline void setMaxFPS(float mMaxFPS)								{ maxFPS = mMaxFPS; renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0); }
			inline void setFPSLimited(bool mFPSLimited)							{ fpsLimited = mFPSLimited; renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0); }
			inline void setPixelMult(unsigned int mPixelMult)					{ pixelMult = mPixelMult; mustRecreate = true; }
			inline void setGameState(GameState& mGameState)						{ gameState = &mGameState; mGameState.gameWindow = this; }

			inline sf::RenderWindow& getRenderWindow()			{ return renderWindow; }
			inline bool getFullscreen() const					{ return fullscreen; }
			inline unsigned int getWidth() const				{ return width; }
			inline unsigned int getHeight() const				{ return height; }
			inline unsigned int getAntialiasingLevel() const	{ return antialiasingLevel; }
			inline Vec2f getMousePosition() const				{ return renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow)); }
			inline bool hasFocus() const						{ return focus; }
			inline bool getVsync() const						{ return vsync; }
			inline bool isFPSLimited() const					{ return fpsLimited; }
			inline float getFPS() const							{ return timer->getFps(); }

			template<typename T> inline T& getTimer() { return static_cast<T&>(*timer); }
			template<typename T, typename... TArgs> inline void setTimer(TArgs&&... mArgs)
			{
				assert(replacementTimer == nullptr);
				replacementTimer = new T{*this, std::forward<TArgs>(mArgs)...}; mustRecreate = true;
			}
	};
}

#endif
