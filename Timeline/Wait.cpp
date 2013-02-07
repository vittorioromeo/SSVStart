// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "Wait.h"
#include "Timeline.h"

namespace ssvs
{
	Wait::Wait(float mTime) : time{mTime}, currentTime{mTime} { }

	void Wait::update(float mFrameTime)
	{
		timelinePtr->ready = false;

		currentTime -= mFrameTime;
		if (currentTime - mFrameTime > mFrameTime) return;

		timelinePtr->next();
		reset();
	}
	void Wait::reset() { currentTime = time; }
} /* namespace sses */
