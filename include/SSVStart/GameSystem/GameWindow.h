// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMEWINDOW
#define SSVS_GAMESYSTEM_GAMEWINDOW

#include <bitset>
#include <cassert>
#include <string>
#include <chrono>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SSVUtils/Delegate/Delegate.h>
#include <SSVUtils/FileSystem/FileSystem.h>
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
			TimerBase* nextTimer{nullptr};

			KeyBitset pressedKeys;
			BtnBitset pressedBtns;

			std::chrono::milliseconds msUpdate, msDraw;

			inline void runUpdate(float mFT)	{ gameState->updateInput(mFT); gameState->update(mFT); }
			inline void runDraw()				{ gameState->draw(); }
			inline void runEvents()
			{
				sf::Event event;
				while(renderWindow.pollEvent(event))
				{
					switch(event.type)
					{
						case sf::Event::Closed:					running = false;										break;
						case sf::Event::GainedFocus:			focus = true;											break;
						case sf::Event::LostFocus:				focus = false;											break;
						case sf::Event::KeyPressed:				pressedKeys[int(event.key.code) + 1] = true;			break;
						case sf::Event::KeyReleased:			pressedKeys[int(event.key.code) + 1] = false;			break;
						case sf::Event::MouseButtonPressed:		pressedBtns[int(event.mouseButton.button) + 1] = true;	break;
						case sf::Event::MouseButtonReleased:	pressedBtns[int(event.mouseButton.button) + 1] = false;	break;
						default:																						break;
					}

					gameState->handleEvent(event);
				}
			}

		public:
			ssvu::Delegate<void()> onRecreation;

			GameWindow() = default;
			GameWindow(const GameWindow&) = delete; // non construction-copyable
			GameWindow& operator=(const GameWindow&) = delete; // non copyable

			inline void run()
			{
				while(running)
				{
					if(mustRecreate) recreateWindow();

					renderWindow.setActive(true);
					renderWindow.clear();

					auto tempMs(std::chrono::high_resolution_clock::now());
					{
						runEvents();
						gameState->refreshInput();
						timer->runUpdate();
						gameState->onPostUpdate();
					}
					msUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - tempMs);

					tempMs = std::chrono::high_resolution_clock::now();
					{
						timer->runDraw();
						renderWindow.display();
					}
					msDraw = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - tempMs);

					timer->runFrameTime();
					timer->runFps();
				}
			}
			inline void stop() noexcept { running = false; }
			inline void recreateWindow()
			{
				if(renderWindow.isOpen()) renderWindow.close();
				renderWindow.create({width, height}, title, fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings{0, 0, antialiasingLevel, 0, 0});
				renderWindow.setSize({width * pixelMult, height * pixelMult});
				renderWindow.setVerticalSyncEnabled(vsync);
				if(nextTimer != nullptr) { timer.reset(nextTimer); nextTimer = nullptr; }
				mustRecreate = false; onRecreation();
			}

			inline void clear(const sf::Color& mColor) { renderWindow.clear(mColor); }
			inline void draw(const sf::Drawable& mDrawable, const sf::RenderStates& mStates = sf::RenderStates::Default) { renderWindow.draw(mDrawable, mStates); }

			inline void saveScreenshot(const ssvu::FileSystem::Path& mPath) const { renderWindow.capture().saveToFile(mPath); }

			inline void setFullscreen(bool mFullscreen) noexcept 					{ fullscreen = mFullscreen; mustRecreate = true; }
			inline void setSize(unsigned int mWidth, unsigned int mHeight) noexcept	{ width = mWidth; height = mHeight; mustRecreate = true; }
			inline void setAntialiasingLevel(unsigned int mLevel) noexcept			{ antialiasingLevel = mLevel; mustRecreate = true; }
			inline void setVsync(bool mEnabled) noexcept							{ vsync = mEnabled; mustRecreate = true;  }
			inline void setMouseCursorVisible(bool mEnabled)						{ renderWindow.setMouseCursorVisible(mEnabled); }
			inline void setTitle(std::string mTitle)								{ title = std::move(mTitle); renderWindow.setTitle(mTitle); }
			inline void setMaxFPS(float mMaxFPS)									{ maxFPS = mMaxFPS; renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0); }
			inline void setFPSLimited(bool mFPSLimited)								{ fpsLimited = mFPSLimited; renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0); }
			inline void setPixelMult(unsigned int mPixelMult) noexcept				{ pixelMult = mPixelMult; mustRecreate = true; }
			inline void setGameState(GameState& mGameState)							{ gameState = &mGameState; mGameState.gameWindow = this; }

			inline operator sf::RenderWindow&() noexcept				{ return renderWindow; }
			inline sf::RenderWindow& getRenderWindow() noexcept			{ return renderWindow; }
			inline bool getFullscreen() const noexcept					{ return fullscreen; }
			inline unsigned int getWidth() const noexcept				{ return width; }
			inline unsigned int getHeight() const noexcept				{ return height; }
			inline unsigned int getAntialiasingLevel() const noexcept	{ return antialiasingLevel; }
			inline bool hasFocus() const noexcept						{ return focus; }
			inline bool getVsync() const noexcept						{ return vsync; }
			inline bool isFPSLimited() const noexcept					{ return fpsLimited; }
			inline float getFPS() const noexcept						{ return timer->getFps(); }
			inline Vec2f getMousePosition() const						{ return renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow)); }
			inline bool isKeyPressed(KKey mKey) const noexcept			{ return pressedKeys[int(mKey) + 1]; }
			inline bool isBtnPressed(MBtn mBtn) const noexcept			{ return pressedBtns[int(mBtn) + 1]; }
			inline const KeyBitset& getPressedKeys() const noexcept		{ return pressedKeys; }
			inline const BtnBitset& getPressedBtns() const noexcept		{ return pressedBtns; }

			inline auto getMsUpdate() const noexcept -> decltype(msUpdate.count())	{ return msUpdate.count(); }
			inline auto getMsDraw() const noexcept -> decltype(msDraw.count())		{ return msDraw.count(); }

			template<typename T> inline T& getTimer() { return reinterpret_cast<T&>(*timer); }
			template<typename T, typename... TArgs> inline void setTimer(TArgs&&... mArgs)
			{
				assert(nextTimer == nullptr);
				nextTimer = new T(*this, std::forward<TArgs>(mArgs)...); mustRecreate = true;
			}
	};
}

#endif

// TODO: refactor!
