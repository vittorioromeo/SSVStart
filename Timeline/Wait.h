#ifndef WAIT_H_
#define WAIT_H_

#include "Command.h"

namespace ssvs
{
	class Wait: public Command
	{
		protected:
			float time;
			float currentTime;
			void update() override;
			void reset() override;

		public:
			Wait(float);
	};

} /* namespace sses */
#endif /* WAIT_H_ */
