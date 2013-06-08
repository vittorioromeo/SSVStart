// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_BIND
#define SSVS_INPUT_BIND

#include <vector>
#include <functional>
#include "SSVStart/Input/Trigger.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		struct Bind
		{
			typedef std::function<void(float)> InputFunc;

			Trigger trigger;
			InputFunc on, off;

			Bind(Trigger mTrigger, InputFunc mOn = nullptr, InputFunc mOff = nullptr);

			void callOn(float mFrameTime) const;
			void callOff(float mFrameTime) const;
		};
	}
}

#endif
