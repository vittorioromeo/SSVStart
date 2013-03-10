// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "Input/Manager.h"
#include "Input/Trigger.h"

using namespace std;

namespace ssvs
{
	namespace Input
	{
		void Manager::add(Trigger mTrigger, InputFunc mInputFunc) { inputFuncPairs.push_back(make_pair(mTrigger, mInputFunc)); }
		void Manager::update(GameWindow& mGameWindow, float mFrameTime)
		{
			for(auto& pair : inputFuncPairs)
			{
				auto& combo(pair.first);
				if(combo.isActive(mGameWindow)) pair.second(mFrameTime);
				combo.updateRelease(mGameWindow);
			}
		}
	}
}

