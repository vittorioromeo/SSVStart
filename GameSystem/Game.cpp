#include "Game.h"
#include "GameWindow.h"
#include <algorithm>

namespace ssvs
{
	void Game::addUpdateFunc(UpdateFunc mUpdateFunc) { updateFuncs.push_back(mUpdateFunc); }
	void Game::addDrawFunc(DrawFunc mDrawFunc, int mPriority = 0) { drawFuncsMap.insert(DrawFuncPair(mPriority, mDrawFunc)); }

	void Game::update(float mFrameTime) { for (auto updateFunc : updateFuncs) updateFunc(mFrameTime); }
	void Game::draw() { for (auto drawFuncPair : drawFuncsMap) drawFuncPair.second(); }
} /* namespace ssvs */
