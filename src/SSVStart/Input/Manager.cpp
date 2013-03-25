// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Input/Manager.h"
#include "SSVStart/Input/Trigger.h"

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
				auto& trigger(pair.first);
				auto& func(pair.second);
				if(trigger.isActive(mGameWindow)) func(mFrameTime);
				trigger.updateRelease(mGameWindow);
			}
		}
	}
}

