// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/GameSystem/GameTimer.hpp"
#include "SSVStart/GameSystem/GameState.hpp"

#include "SSVStart/Input/InputState.hpp"

#include <SFML/Window/Event.hpp>

#include <cassert>

namespace ssvs
{

class GameWindow;

class GameEngine
{
    friend GameWindow;
    friend class TimerBase;
    friend class TimerStatic;
    friend class TimerDynamic;

private:
    GameTimer timer;
    GameState* gameState{nullptr};
    Input::InputState* inputState{nullptr};
    bool running{true};

    void refreshTimer()
    {
        timer.refresh();
    }

    // These methods are called from the timer
    void updateFromTimer(FT mFT)
    {
        assert(isValid());

        if(inputState != nullptr)
        {
            gameState->updateInput(*inputState, mFT);
        }

        gameState->update(mFT);
    }

    void drawFromTimer()
    {
        assert(isValid());
        gameState->draw();
    }

    void handleEvent(const sf::Event& mEvent) const noexcept
    {
        assert(isValid());
        gameState->handleEvent(mEvent);
    }

    [[nodiscard]] bool isValid() const noexcept
    {
        return gameState != nullptr;
    }

public:
    GameEngine() = default;

    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;

    void stop() noexcept
    {
        running = false;
    }

    void runUpdate()
    {
        assert(isValid());

        if(inputState != nullptr) gameState->refreshInput(*inputState);
        timer->runUpdate();
        gameState->onPostUpdate();
    }

    void runDraw()
    {
        assert(isValid());

        timer->runDraw();
    }

    void runFPS()
    {
        assert(isValid());

        timer->runFrameTime();
        timer->runFPS();
    }

    [[nodiscard]] float getFPS() const noexcept
    {
        return timer->getFPS();
    }

    void setGameState(GameState& mGameState) noexcept
    {
        gameState = &mGameState;
    }

    void setInputState(Input::InputState& mInputState) noexcept
    {
        inputState = &mInputState;
    }

    [[nodiscard]] bool isRunning() const noexcept
    {
        return running;
    }

    template <typename T>
    [[nodiscard]] T& getTimer()
    {
        return timer.getImpl<T>();
    }

    [[nodiscard]] TimerBase& getTimerBase() noexcept
    {
        return timer.getBase();
    }

    template <typename T, typename... TArgs>
    void setTimer(TArgs&&... mArgs)
    {
        timer.setImpl<T>(*this, FWD(mArgs)...);
    }
};

} // namespace ssvs
