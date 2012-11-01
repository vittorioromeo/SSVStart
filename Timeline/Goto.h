#ifndef GOTO_H_
#define GOTO_H_

#include "Command.h"

namespace ssvs
{
	class Goto: public Command
	{
		protected:
			int targetIndex;
			int times;
			int currentTimes;

			void update() override;
			void reset() override;

		public:
			Goto(int, int);
	};
} /* namespace ssvs */
#endif /* GOTO_H_ */
