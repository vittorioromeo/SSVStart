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

#ifndef TIMELINE_H_
#define TIMELINE_H_

#include <vector>
#include <functional>

namespace ssvs
{
	typedef std::function<void()> Action;

	class Command;

	class Timeline
	{
		friend class Wait;
		friend class Do;
		friend class Go;

		private:
			std::vector<Command*> commandPtrs; // owned
			Command* currentCommandPtr{nullptr};

			bool ready{true};
			bool finished{false};

			void push_back(Command* mCommandPtr);
			void next();

		public:
			~Timeline();

			void insert(int mIndex, Command* mCommandPtr);			
			void del(Command* mCommandPtr);
			
			void update(float mFrameTime);
			void jumpTo(int mIndex);

			void reset();
			void clear();

			int getSize();
			int getCurrentIndex();
			bool getFinished();

			// Shortcuts
			Timeline& operator+=(Action mAction);
			void wait(float mTime);
			void go(int mTargetIndex, int mTimes = -1);
	};
} /* namespace sses */
#endif /* TIMELINE_H_ */
