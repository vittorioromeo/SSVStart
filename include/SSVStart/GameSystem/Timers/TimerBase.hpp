// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include <SSVUtils/Core/Common/Frametime.hpp>

#include <SFML/System/Clock.hpp>

namespace ssvs
{

class GameEngine;

class TimerBase
{
protected:
    GameEngine& gameEngine;
    sf::Clock clock;
    FT frameTime{0};
    float fps{0};

public:
    TimerBase(GameEngine& mGameEngine) noexcept : gameEngine(mGameEngine)
    {
    }

    virtual ~TimerBase()
    {
    }

    virtual void runUpdate()
    {
    }

    virtual void runFrameTime() final
    {
        frameTime = ssvu::getSecondsToFT(clock.restart().asSeconds());
    }

    virtual void runFPS()
    {
        fps = ssvu::getFTToFPS(frameTime);
    }

    virtual void runDraw() final;

    FT getFrameTime() const noexcept
    {
        return frameTime;
    }

    float getFPS() const noexcept
    {
        return fps;
    }
};

} // namespace ssvs
