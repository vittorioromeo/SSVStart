// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMEENGINE
#define SSVS_GAMESYSTEM_GAMEENGINE

#include <chrono>
#include <SFML/Window.hpp>
#include <SSVUtils/Core/Core.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/GameSystem/GameState.hpp"
#include "SSVStart/GameSystem/GameTimer.hpp"
#include "SSVStart/Input/InputState.hpp"

namespace ssvs
{
	class GameWindow;

	class GameEngine : ssvu::NoCopy
	{
		friend class GameWindow;
		friend class TimerBase;
		friend class TimerStatic;
		friend class TimerDynamic;

		private:
			GameTimer timer;
			GameState* gameState{nullptr};
			Input::InputState* inputState{nullptr};
			bool running{true};

			inline void refreshTimer() { timer.refresh(); }

			// These methods are called from the timer
			inline void updateFromTimer(FT mFT)
			{
				SSVU_ASSERT(isValid());
				if(inputState != nullptr) gameState->updateInput(*inputState, mFT);
				gameState->update(mFT);
			}
			inline void drawFromTimer()
			{
				SSVU_ASSERT(isValid());
				gameState->draw();
			}

			inline void handleEvent(const sf::Event& mEvent) const noexcept
			{
				SSVU_ASSERT(isValid());
				gameState->handleEvent(mEvent);
			}

			inline bool isValid() const noexcept { return gameState != nullptr; }

		public:
			inline void stop() noexcept { running = false; }

			inline void runUpdate()
			{
				SSVU_ASSERT(isValid());

				if(inputState != nullptr) gameState->refreshInput(*inputState);
				timer->runUpdate();
				gameState->onPostUpdate();
			}

			inline void runDraw()
			{
				SSVU_ASSERT(isValid());

				timer->runDraw();
			}

			inline void runFPS()
			{
				SSVU_ASSERT(isValid());

				timer->runFrameTime();
				timer->runFps();
			}

			inline float getFPS() const noexcept	{ return timer->getFps(); }

			inline void setGameState(GameState& mGameState) noexcept			{ gameState = &mGameState; }
			inline void setInputState(Input::InputState& mInputState) noexcept	{ inputState = &mInputState; }

			inline bool isRunning() const noexcept { return running; }

			template<typename T> inline T& getTimer() { return timer.getImpl<T>(); }
			template<typename T, typename... TArgs> inline void setTimer(TArgs&&... mArgs) { timer.setImpl<T>(*this, std::forward<TArgs>(mArgs)...); }
	};
}

#endif
