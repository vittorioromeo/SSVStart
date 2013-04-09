// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/GameState.h"

using namespace std;
using namespace sf;
using namespace ssvs::Input;

namespace ssvs
{
	void GameState::addInput(Trigger mTrigger, IFunc mInputFunc, ITypes mType) { mTrigger.setType(mType); inputManager.add(mTrigger, mInputFunc); }

	GameState::EventDelegate& GameState::getEventDelegate(Event::EventType mEventType)
	{
		return eventDelegates[mEventType];
	}

	void GameState::update(float mFrameTime) { onUpdate(mFrameTime); }
	void GameState::updateInput(float mFrameTime) { inputManager.update(*gameWindowPtr, mFrameTime); }

	void GameState::updateInputRelease() { inputManager.updateRelease(*gameWindowPtr); }
	void GameState::draw() { onDraw(); }

	void GameState::handleEvent(const Event& mEvent) { eventDelegates[mEvent.type](mEvent); }
}
