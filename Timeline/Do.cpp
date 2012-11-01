#include "Do.h"
#include "Timeline.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace ssvs
{
	Do::Do(Action mAction) : action(mAction) { }
	void Do::update()
	{
		action();
		timelinePtr->next();
	}
} /* namespace sses */
