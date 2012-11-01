#ifndef TIMELINE_H_
#define TIMELINE_H_

#include <vector>

using namespace std;

namespace ssvs
{
	class Command;

	class Timeline
	{
		friend class Wait;
		friend class Do;
		friend class Goto;

		private:
			vector<Command*> commandPtrs; // owned
			Command* currentCommandPtr { nullptr };

			float timeNext { 0 };
			bool ready { true };
			bool finished { false };

			void next();
			void step();

		public:
			~Timeline();

			bool isFinished();
			void add(Command*);
			void del(Command*);
			void update(float);
			void jumpTo(int);
			void reset();
	};
} /* namespace sses */
#endif /* TIMELINE_H_ */
