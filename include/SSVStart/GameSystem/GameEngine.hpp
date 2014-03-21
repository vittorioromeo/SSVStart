// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMEENGINE
#define SSVS_GAMESYSTEM_GAMEENGINE

#include <bitset>
#include <cassert>
#include <string>
#include <chrono>
#include <SFML/Window.hpp>
#include <SSVUtils/Core/Core.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/GameSystem/GameState.hpp"
#include "SSVStart/GameSystem/GameTimer.hpp"

namespace ssvs
{
	class InputState;
	class GameWindow;

	class GameEngine : ssvu::NoCopy
	{
		friend class GameWindow;
		friend class TimerBase;
		friend class TimerStatic;
		friend class TimerDynamic;

		private:
			GameState* gameState{nullptr};
			InputState* inputState{nullptr};
			bool running{true};

			GameTimer timer;

			FT msUpdate, msDraw;

			inline void refreshTimer() { timer.refresh(); }

			// These methods are called from the timer
			inline void updateFromTimer(FT mFT)
			{
				if(inputState != nullptr) updateGameStateInput(mFT);
				updateGameState(mFT);
			}
			inline void drawFromTimer() { drawGameState(); }

			inline void updateGameState(FT mFT)								{ SSVU_ASSERT(isValid()); gameState->update(mFT); }
			inline void refreshGameStateInput()								{ SSVU_ASSERT(isValid()); gameState->refreshInput(*inputState); }
			inline void updateGameStateInput(FT mFT)						{ SSVU_ASSERT(isValid()); gameState->updateInput(*inputState, mFT); }
			inline void drawGameState()										{ SSVU_ASSERT(isValid()); gameState->draw(); }
			inline void handleEvent(const sf::Event& mEvent) const noexcept	{ SSVU_ASSERT(isValid()); gameState->handleEvent(mEvent); }

			inline bool isValid() const noexcept { return gameState != nullptr; }

		public:
			inline void stop() noexcept { running = false; }

			inline void runUpdate()
			{
				SSVU_ASSERT(isValid());

				auto tempMs(HRClock::now());
				{
					if(inputState != nullptr) refreshGameStateInput();
					timer->runUpdate();
					gameState->onPostUpdate();
				}
				msUpdate = std::chrono::duration_cast<FTDuration>(HRClock::now() - tempMs).count();
			}

			inline void runDraw()
			{
				SSVU_ASSERT(isValid());

				auto tempMs(HRClock::now());
				{
					timer->runDraw();
				}
				msDraw = std::chrono::duration_cast<FTDuration>(HRClock::now() - tempMs).count();
			}

			inline void runFPS()
			{
				SSVU_ASSERT(isValid());

				timer->runFrameTime();
				timer->runFps();
			}

			inline FT getMsUpdate() const noexcept	{ return msUpdate; }
			inline FT getMsDraw() const noexcept	{ return msDraw; }
			inline float getFPS() const noexcept	{ return timer->getFps(); }

			inline void setGameState(GameState& mGameState) noexcept			{ gameState = &mGameState; }
			inline void setInputState(InputState& mInputState) noexcept	{ inputState = &mInputState; }

			inline bool isRunning() const noexcept { return running; }

			template<typename T> inline T& getTimer() { return timer.getImpl<T>(); }
			template<typename T, typename... TArgs> inline void setTimer(TArgs&&... mArgs) { timer.setImpl<T>(*this, std::forward<TArgs>(mArgs)...); }
	};
}

#endif
