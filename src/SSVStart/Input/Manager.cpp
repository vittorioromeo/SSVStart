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
		void Manager::add(const Bind& mBind) { binds.push_back(mBind); }
		void Manager::update(GameWindow& mGameWindow, float mFrameTime)
		{
			for(auto& b : binds) b.trigger.isActive(mGameWindow) ? b.callOn(mFrameTime) : b.callOff(mFrameTime);
		}
		void Manager::refresh(GameWindow& mGameWindow) { for(auto& b : binds) b.trigger.refresh(mGameWindow); }
	}
}
