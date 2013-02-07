// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "GameState.h"
#include "GameWindow.h"
#include <algorithm>

namespace ssvs
{
	void GameState::addUpdateFunc(UpdateFunc mUpdateFunc) { updateFuncs.push_back(mUpdateFunc); }
	void GameState::addDrawFunc(DrawFunc mDrawFunc, int mPriority) { drawFuncsMap.insert(DrawFuncPair(mPriority, mDrawFunc)); }

	void GameState::update(float mFrameTime) { for (auto& updateFunc : updateFuncs) updateFunc(mFrameTime); }
	void GameState::draw() { for (auto& drawFuncPair : drawFuncsMap) drawFuncPair.second(); }
} /* namespace ssvs */
