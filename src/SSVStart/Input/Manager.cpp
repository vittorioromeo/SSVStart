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
		void Manager::add(Trigger mTrigger, InputFunc mInputFunc) { pairs.emplace_back(mTrigger, mInputFunc); }
		void Manager::update(GameWindow& mGameWindow, float mFrameTime) { for(auto& p : pairs) if(p.first.isActive(mGameWindow)) p.second(mFrameTime); }
		void Manager::refresh(GameWindow& mGameWindow) { for(auto& p : pairs) p.first.updateRelease(mGameWindow); }
	}
}

