#include "InputManager.h"

using namespace std;

namespace ssvs
{
	void InputManager::addInput(InputCombo mInputCombination, InputFunc mInputFunc)
	{
		inputFuncPairs.push_back(make_pair(mInputCombination, mInputFunc));
	}
	void InputManager::update(GameWindow& mGameWindow, float mFrameTime)
	{
		for(auto& pair : inputFuncPairs)
		{
			auto& inputCombo(pair.first);

			if(inputCombo.isActive(mGameWindow)) pair.second(mFrameTime);
			inputCombo.updateRelease(mGameWindow);
		}
	}
}

