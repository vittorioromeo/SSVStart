// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Input/Input.hpp"

#include <SSVUtils/Delegate/Delegate.hpp>

#include <SFML/Window/Event.hpp>

#include <map>

namespace ssvs
{

class GameEngine;

class GameState
{
    friend GameEngine;

private:
    using ITrigger = Input::Trigger;
    using IType = Input::Type;
    using IMode = Input::Mode;
    using IFunc = InputFunc;
    using EventDelegate = ssvu::Delegate<void(const sf::Event&)>;

    Input::Manager inputManager;
    std::map<sf::Event::EventType, EventDelegate> eventDelegates;

    void handleEvent(const sf::Event& mEvent)
    {
        onAnyEvent(mEvent);
        eventDelegates[mEvent.type](mEvent);
    }

    void update(ssvu::FT mFT)
    {
        onUpdate(mFT);
    }

    void draw()
    {
        onDraw();
    }

    void updateInput(Input::InputState& mInputState, ssvu::FT mFT)
    {
        inputManager.update(mInputState, mFT);
    }

    void refreshInput(Input::InputState& mInputState)
    {
        inputManager.refresh(mInputState);
    }

public:
    ssvu::Delegate<void()> onDraw, onPostUpdate;
    ssvu::Delegate<void(ssvu::FT)> onUpdate;
    EventDelegate onAnyEvent;

    GameState() = default;

    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;

    auto& addInput(ITrigger mTrigger, IFunc mFuncOn, IFunc mFuncOff,
        IType mType = IType::Always, int mTriggerID = -1,
        IMode mMode = IMode::Overlap)
    {
        return inputManager.emplace(
            mTrigger, mType, mMode, mTriggerID, mFuncOn, mFuncOff);
    }

    auto& addInput(ITrigger mTrigger, IFunc mFuncOn,
        IType mType = IType::Always, int mTriggerID = -1,
        IMode mMode = IMode::Overlap)
    {
        return addInput(mTrigger, mFuncOn, Impl::getNullInputFunc(), mType,
            mTriggerID, mMode);
    }

    void refreshTrigger(const Input::Trigger& trigger, int bindID)
    {
        inputManager.refreshTriggers(trigger, bindID);
    }

    auto& onEvent(sf::Event::EventType mEventType)
    {
        return eventDelegates[mEventType];
    }

    void ignoreNextInputs() noexcept
    {
        inputManager.ignoreNextInputs();
    }

    void ignoreAllInputs(bool mIgnore) noexcept
    {
        inputManager.ignoreAllInputs(mIgnore);
    }
};

} // namespace ssvs
