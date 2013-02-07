// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "Go.h"
#include "Timeline.h"

namespace ssvs
{
	Go::Go(int mTargetIndex, int mTimes = -1) : targetIndex{mTargetIndex}, times{mTimes}, currentTimes{mTimes} { }

	void Go::update(float)
	{
		if (currentTimes <= 0) timelinePtr->next();
		else
		{
			currentTimes--;
			timelinePtr->jumpTo(targetIndex);
		}
	}
	void Go::reset() { currentTimes = times; }
} /* namespace ssvs */
