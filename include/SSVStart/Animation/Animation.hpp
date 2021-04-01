// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Global/Typedefs.hpp"

#include <vector>
#include <initializer_list>

namespace ssvs
{

struct AnimationStep
{
    Vec2u index;
    float time;
};

class Animation
{
public:
    enum class Type
    {
        Once,
        Loop,
        PingPong
    };

private:
    std::vector<AnimationStep> steps;
    unsigned int index{0};
    float speed{1.f}, time{0.f};
    int dir{1};
    Type type;
    unsigned int currentTarget{0u}, nextTarget{0u};

    void refreshTargets() noexcept
    {
        if(dir > 0)
        {
            currentTarget = steps.size() - 1;
            nextTarget = 0u;
        }
        else
        {
            currentTarget = 0u;
            nextTarget = steps.size() - 1;
        }
    }

    void nextStep() noexcept
    {
        SSVU_ASSERT(index < steps.size());

        time = 0;

        if(dir > 0 ? index < currentTarget : index > 0u)
        {
            index += dir;
        }
        else if(type == Type::Loop)
        {
            index = nextTarget;
        }
        else if(type == Type::PingPong)
        {
            dir *= -1;
            refreshTargets();
            index += dir;
        }
    }

public:
    Animation(Type mType = Type::Loop) noexcept : type{mType}
    {
    }

    void addStep(const AnimationStep& mStep)
    {
        steps.emplace_back(mStep);
        refreshTargets();
    }

    void addSteps(const std::initializer_list<AnimationStep>& mSteps)
    {
        for(const auto& s : mSteps) addStep(s);
    }

    void addSteps(const std::initializer_list<Vec2u>& mIndexes, float mStepTime)
    {
        for(const auto& i : mIndexes) addStep({i, mStepTime});
    }

    void setSpeed(float mSpeed) noexcept
    {
        speed = mSpeed;
    }

    void setType(Type mType) noexcept
    {
        type = mType;
    }

    void setReverse(bool mReverse) noexcept
    {
        dir = mReverse ? -1 : 1;
        refreshTargets();
    }

    float getSpeed() const noexcept
    {
        return speed;
    }

    float getTime() const noexcept
    {
        return time;
    }

    unsigned int getIdx() const noexcept
    {
        return index;
    }

    bool isReverse() const noexcept
    {
        return dir == -1;
    }

    auto getType() const noexcept
    {
        return type;
    }

    const auto& getStep() const
    {
        return steps[index];
    }

    auto getTileIndex() const
    {
        return getStep().index;
    }

    void update(FT mFT)
    {
        if(steps.empty()) return;

        time += mFT * speed;
        if(time >= getStep().time) nextStep();
    }
};

} // namespace ssvs
