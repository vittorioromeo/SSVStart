// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Input/Bind.h"

using namespace std;

namespace ssvs
{
	namespace Input
	{
		Bind::Bind(Trigger mTrigger, InputFunc mOn, InputFunc mOff) : trigger{mTrigger}, on{mOn}, off{mOff} { }

		void Bind::callOn(float mFrameTime) const	{ if(on != nullptr) on(mFrameTime); }
		void Bind::callOff(float mFrameTime) const	{ if(off != nullptr) off(mFrameTime); }
	}
}
