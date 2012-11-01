#ifndef DO_H_
#define DO_H_

#include "Command.h"
#include <functional>

using namespace std;

namespace ssvs
{
	class Do: public Command
	{
		typedef function<void()> Action;

		protected:
			Action action;
			void update() override;

		public:
			Do(Action);
	};
} /* namespace sses */
#endif /* DO_H_ */
