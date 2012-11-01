#include "Game.h"
#include <algorithm>

namespace ssvs
{
	void Game::addUpdateFunc(updateFuncType mUpdateFunc)
	{
		updateFuncs.push_back(mUpdateFunc);
	}
	void Game::addDrawFunc(drawFuncType mDrawFunc, int mPriority = 0)
	{
		drawFuncsMap.insert(updateFuncPair(mPriority, mDrawFunc));
	}
	
	void Game::update(float mFrameTime)
	{
		for (auto updateFunc : updateFuncs)
			updateFunc(mFrameTime);
	}
	void Game::draw()
	{
		for (auto drawFuncPair : drawFuncsMap)
			drawFuncPair.second();
	}
} /* namespace ssvs */
