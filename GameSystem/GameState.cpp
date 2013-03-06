// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "GameState.h"
#include "GameWindow.h"
#include <algorithm>

using namespace ssvs::Input;

namespace ssvs
{
	void GameState::addInput(Trigger mTrigger, Manager::InputFunc mInputFunc, Trigger::Types mType)
	{
		mTrigger.setType(mType); inputManager.addInput(mTrigger, mInputFunc);
	}
	void GameState::update(float mFrameTime)
	{
		inputManager.update(*gameWindowPtr, mFrameTime);
		onUpdate(mFrameTime);
	}
	void GameState::draw() { onDraw(); }

}
