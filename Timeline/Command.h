#ifndef COMMAND_H_
#define COMMAND_H_

#include "Timeline.h"

namespace ssvs
{
	class Command
	{
		friend class Timeline;

		protected:
			Timeline* timelinePtr;

			virtual ~Command();
			virtual void initialize();
			virtual void update();
			virtual void reset();
	};
} /* namespace ssvs */
#endif /* COMMAND_H_ */
