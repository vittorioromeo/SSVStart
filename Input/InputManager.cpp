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
			pair.first.updateRelease(mGameWindow);
			
			if(pair.first.isActive(mGameWindow))
			{
				pair.second(mFrameTime);
				pair.first.setReleased(false);
			}
		}
	}
}

