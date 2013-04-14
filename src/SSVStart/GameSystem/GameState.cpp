// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/GameState.h"

using namespace std;
using namespace sf;
using namespace ssvs::Input;

namespace ssvs
{
	void GameState::addInput(Trigger mTrigger, IFunc mFuncOn, ITypes mType) { mTrigger.setType(mType); inputManager.add({mTrigger, mFuncOn}); }
	void GameState::addInput(Trigger mTrigger, IFunc mFuncOn, IFunc mFuncOff, ITypes mType)
	{
		mTrigger.setType(mType); inputManager.add({mTrigger, mFuncOn, mFuncOff});
	}

	GameState::EventDelegate& GameState::getEventDelegate(Event::EventType mEventType) { return eventDelegates[mEventType]; }

	void GameState::update(float mFrameTime) { onUpdate(mFrameTime); }
	void GameState::updateInput(float mFrameTime) { inputManager.update(*gameWindowPtr, mFrameTime); }

	void GameState::refreshInput() { inputManager.refresh(*gameWindowPtr); }
	void GameState::draw() { onDraw(); }

	void GameState::handleEvent(const Event& mEvent) { eventDelegates[mEvent.type](mEvent); }
}
