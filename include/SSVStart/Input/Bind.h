// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_BIND
#define SSVS_INPUT_BIND

#include <vector>
#include <functional>
#include "SSVStart/Input/Trigger.h"
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Bind
		{
			private:
				Trigger trigger;
				InputFunc on, off;

			public:
				Bind(Trigger mTrigger, InputFunc mOn = nullptr, InputFunc mOff = nullptr) : trigger{mTrigger}, on{mOn}, off{mOff} { }

				inline void update(float mFrameTime, GameWindow& mGameWindow)	{ trigger.isActive(mGameWindow) ? callOn(mFrameTime) : callOff(mFrameTime); }
				inline void refresh(GameWindow& mGameWindow)					{ trigger.refresh(mGameWindow); }

				inline void callOn(float mFrameTime) const	{ if(on != nullptr) on(mFrameTime); }
				inline void callOff(float mFrameTime) const	{ if(off != nullptr) off(mFrameTime); }
		};
	}
}

#endif
