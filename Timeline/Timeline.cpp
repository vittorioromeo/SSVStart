#include "Timeline.h"
#include "Command.h"
#include "../Utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

namespace ssvs
{
	Timeline::~Timeline()
	{
		for (auto commandPtr : commandPtrs) delete commandPtr;
	}

	bool Timeline::isFinished() { return finished; }
	void Timeline::add(Command* mCommandPtr)
	{
		mCommandPtr->timelinePtr = this;
		mCommandPtr->initialize();
		commandPtrs.push_back(mCommandPtr);
		if(currentCommandPtr == nullptr) currentCommandPtr = mCommandPtr;
	}
	void Timeline::del(Command* mCommandPtr)
	{
		delFromVector<Command*>(commandPtrs, mCommandPtr);
		delete mCommandPtr;
	}
	void Timeline::next()
	{
		auto iter = find(commandPtrs.begin(), commandPtrs.end(), currentCommandPtr);
		if (iter == commandPtrs.end() - 1)
		{
			currentCommandPtr = nullptr; // no more commands
			return;
		}
		else
		{
			iter++;
			currentCommandPtr = *iter;
		}
	}
	void Timeline::step()
	{
		do
		{
			if (currentCommandPtr == nullptr)
			{
				finished = true;
				ready = false;
				break;
			}

			currentCommandPtr->update();
		} while (ready);
	}
	void Timeline::update(float mFrameTime)
	{
		timeNext += mFrameTime;
		if (timeNext < 1) return;

		auto remainder = timeNext - floor(timeNext);

		if (finished) return;
		ready = true;

		for (int i = 0; i < floor(timeNext); i++) step();

		timeNext = remainder;
	}
	void Timeline::jumpTo(int mTargetIndex) { currentCommandPtr = commandPtrs[mTargetIndex]; }
	void Timeline::reset()
	{
		finished = false;
		for (auto commandPtr : commandPtrs) commandPtr->reset();

		if(commandPtrs.size() > 0) currentCommandPtr = commandPtrs[0];
		else currentCommandPtr = nullptr;
	}
} /* namespace sses */
