// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/GameSystem/Timers/TimerBase.hpp"
#include "SSVStart/GameSystem/GameEngine.hpp"

#include <SSVUtils/Core/Common/Frametime.hpp>

namespace ssvs
{

class TimerStatic final : public TimerBase
{
private:
    ssvu::FT step, timeSlice, time{0};
    float maxLoops, loops{0};

public:
    TimerStatic(GameEngine& mGameEngine, ssvu::FT mStep = 1.f,
        ssvu::FT mTimeSlice = 1.f, float mMaxLoops = 50.f) noexcept
        : TimerBase(mGameEngine), step{mStep}, timeSlice{mTimeSlice},
          maxLoops{mMaxLoops}
    {
    }

    void reset() override
    {
        time = loops = 0;
    }

    void runUpdate() override
    {
        loops = 0;
        time += frameTime;

        while(time >= timeSlice && loops < maxLoops)
        {
            gameEngine.updateFromTimer(step);
            time -= timeSlice;
            ++loops;
        }
    }

    void setStep(ssvu::FT mStep) noexcept
    {
        step = mStep;
    }

    void setTimeSlice(ssvu::FT mTimeSlice) noexcept
    {
        timeSlice = mTimeSlice;
    }

    void setMaxLoops(float mMaxLoops) noexcept
    {
        maxLoops = mMaxLoops;
    }

    [[nodiscard]] ssvu::FT getStep() const noexcept
    {
        return step;
    }

    [[nodiscard]] ssvu::FT getTimeSlice() const noexcept
    {
        return timeSlice;
    }

    [[nodiscard]] ssvu::FT getTime() const noexcept
    {
        return time;
    }

    [[nodiscard]] float getMaxLoops() const noexcept
    {
        return maxLoops;
    }

    [[nodiscard]] float getLoops() const noexcept
    {
        return loops;
    }
};

} // namespace ssvs
