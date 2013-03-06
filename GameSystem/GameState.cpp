// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "GameState.h"
#include "GameWindow.h"
#include <algorithm>

namespace ssvs
{
	void GameState::addInput(InputCombo mInputCombination, InputManager::InputFunc mInputFunc,
		InputCombo::Types mType) { mInputCombination.setType(mType); inputManager.addInput(mInputCombination, mInputFunc); }
	void GameState::update(float mFrameTime)
	{
		inputManager.update(*gameWindowPtr, mFrameTime);
		onUpdate(mFrameTime);
	}
	void GameState::draw() { onDraw(); }

}
