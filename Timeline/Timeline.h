// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

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
