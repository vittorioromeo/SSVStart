/* The MIT License (MIT)
 * Copyright (c) 2012 Vittorio Romeo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

	void Timeline::insert(int mIndex, Command* mCommandPtr)
	{
		mCommandPtr->timelinePtr = this;
		mCommandPtr->initialize();
		commandPtrs.insert(commandPtrs.begin() + mIndex, mCommandPtr);
		if(currentCommandPtr == nullptr) currentCommandPtr = mCommandPtr;
	}
	void Timeline::push_back(Command* mCommandPtr)
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
		if(currentCommandPtr == nullptr) return;
		
		auto iter = find(commandPtrs.begin(), commandPtrs.end(), currentCommandPtr);
		if (iter == commandPtrs.end() - 1)
		{
			currentCommandPtr = nullptr; // no more commands
			return;
		}
		else if (iter < commandPtrs.end() - 1 && iter >= commandPtrs.begin())
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

		if(!commandPtrs.empty()) currentCommandPtr = commandPtrs[0];
		else currentCommandPtr = nullptr;
	}
	void Timeline::clear()
	{
		currentCommandPtr = nullptr;
		for (auto commandPtr : commandPtrs) delete commandPtr;
		commandPtrs.clear();
		finished = true;
	}
	int Timeline::getSize() { return commandPtrs.size(); }
	int Timeline::getCurrentIndex()
	{
		int pos = find(commandPtrs.begin(), commandPtrs.end(), currentCommandPtr) - commandPtrs.begin();

		if( pos < commandPtrs.size() )
			return pos;

		cout << "not found";
		return -1;
	}
} /* namespace sses */
