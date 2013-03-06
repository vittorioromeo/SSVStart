#include "Input/Manager.h"
#include "Input/Trigger.h"

using namespace std;

namespace ssvs
{
	namespace Input
	{
		void Manager::addInput(Trigger mTrigger, InputFunc mInputFunc)
		{
			inputFuncPairs.push_back(make_pair(mTrigger, mInputFunc));
		}
		void Manager::update(GameWindow& mGameWindow, float mFrameTime)
		{
			for(auto& pair : inputFuncPairs)
			{
				auto& inputCombo(pair.first);

				if(inputCombo.isActive(mGameWindow)) pair.second(mFrameTime);
				inputCombo.updateRelease(mGameWindow);
			}
		}
	}
}

