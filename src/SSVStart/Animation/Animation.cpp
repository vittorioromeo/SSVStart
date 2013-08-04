// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Animation/Animation.h"

namespace ssvs
{
	void Animation::nextStep()
	{
		int lastIndex{currentIndex};
		reverse ? --currentIndex : ++currentIndex;

		if(currentIndex >= static_cast<int>(steps.size()))
		{
			if(loop)
			{
				if(pingPong) { reverse = !reverse; currentIndex = lastIndex; }
				else currentIndex = 0;
			}
			else currentIndex = lastIndex;
		}
		else if(currentIndex < 0)
		{
			if(loop)
			{
				if(pingPong) { reverse = !reverse; currentIndex = lastIndex; }
				else currentIndex = steps.size() - 1;
			}
			else currentIndex = lastIndex;
		}

		currentTime = 0;
	}

	void Animation::update(float mFrameTime)
	{
		if(steps.empty()) return;

		currentTime += mFrameTime * speed;
		if(currentTime >= getCurrentStep().time) nextStep();
	}
}
