// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

namespace ssvs
{

class TimerStatic final : public TimerBase
{
private:
    FT step, timeSlice, time{0};
    float maxLoops, loops{0};

public:
    TimerStatic(GameEngine& mGameEngine, FT mStep = 1.f, FT mTimeSlice = 1.f,
        float mMaxLoops = 50.f) noexcept
        : TimerBase(mGameEngine), step{mStep}, timeSlice{mTimeSlice},
          maxLoops{mMaxLoops}
    {
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

    void setStep(FT mStep) noexcept
    {
        step = mStep;
    }
    void setTimeSlice(FT mTimeSlice) noexcept
    {
        timeSlice = mTimeSlice;
    }
    void setMaxLoops(float mMaxLoops) noexcept
    {
        maxLoops = mMaxLoops;
    }

    FT getStep() const noexcept
    {
        return step;
    }
    FT getTimeSlice() const noexcept
    {
        return timeSlice;
    }
    FT getTime() const noexcept
    {
        return time;
    }
    float getMaxLoops() const noexcept
    {
        return maxLoops;
    }
    float getLoops() const noexcept
    {
        return loops;
    }
};

} // namespace ssvs
