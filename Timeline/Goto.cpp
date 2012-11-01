#include "Goto.h"

namespace ssvs
{
	Goto::Goto(int mTargetIndex, int mTimes = -1) : targetIndex(mTargetIndex), times(mTimes), currentTimes(mTimes) { }

	void Goto::update()
	{
		if (currentTimes <= 0) timelinePtr->next();
		else
		{
			currentTimes--;
			timelinePtr->jumpTo(targetIndex);
		}
	}
	void Goto::reset() { currentTimes = times; }
} /* namespace ssvs */
