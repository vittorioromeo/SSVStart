#include "Wait.h"

namespace ssvs
{
	Wait::Wait(float mTime) : time(mTime), currentTime(mTime) { }

	void Wait::update()
	{
		timelinePtr->ready = false;

		currentTime--;
		if (currentTime > 0) return;

		timelinePtr->next();
		reset();
	}
	void Wait::reset() { currentTime = time; }
} /* namespace sses */
