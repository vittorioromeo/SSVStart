// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/GameSystem/Timers/TimerBase.hpp"
#include "SSVStart/GameSystem/GameEngine.hpp"

namespace ssvs {

class TimerStatic final : public TimerBase
{
private:
    float step, timeSlice, time{0};
    float maxLoops, loops{0};

public:
    TimerStatic(GameEngine& mGameEngine, float mStep = 1.f,
        float mTimeSlice = 1.f, float mMaxLoops = 50.f) noexcept
        : TimerBase(mGameEngine),
          step{mStep},
          timeSlice{mTimeSlice},
          maxLoops{mMaxLoops}
    {}

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

    void setStep(float mStep) noexcept
    {
        step = mStep;
    }

    void setTimeSlice(float mTimeSlice) noexcept
    {
        timeSlice = mTimeSlice;
    }

    void setMaxLoops(float mMaxLoops) noexcept
    {
        maxLoops = mMaxLoops;
    }

    [[nodiscard]] float getStep() const noexcept
    {
        return step;
    }

    [[nodiscard]] float getTimeSlice() const noexcept
    {
        return timeSlice;
    }

    [[nodiscard]] float getTime() const noexcept
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
