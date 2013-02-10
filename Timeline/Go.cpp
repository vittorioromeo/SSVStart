// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "Go.h"

namespace ssvs
{
	Go::Go(Timeline& mTimeline, int mTargetIndex, int mTimes = -1) : Command{mTimeline}, targetIndex{mTargetIndex}, times{mTimes}, currentTimes{mTimes} { }

	void Go::update(float)
	{
		if (currentTimes <= 0) timeline.next();
		else
		{
			currentTimes--;
			timeline.jumpTo(targetIndex);
		}
	}
	void Go::reset() { currentTimes = times; }
}
