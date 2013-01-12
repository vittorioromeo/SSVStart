#include "InputManager.h"

using namespace std;

namespace ssvs
{
	void InputManager::addInput(InputCombination mInputCombination, InputFunc mInputFunc) { inputFuncPairs.push_back(make_pair(mInputCombination, mInputFunc)); }
	void InputManager::update(GameWindow& mGameWindow, float mFrameTime)
	{
		for (auto& inputFuncPair : inputFuncPairs) if(inputFuncPair.first.isDown(mGameWindow)) inputFuncPair.second(mFrameTime);
	}
}

