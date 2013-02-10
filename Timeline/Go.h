// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef GOTO_H_
#define GOTO_H_

#include "Command.h"

namespace ssvs
{
	class Go : public Command
	{
		protected:
			int targetIndex;
			int times;
			int currentTimes;

			void update(float mFrameTime) override;
			void reset() override;

		public:
			Go(Timeline& mTimeline, int, int);
	};
} /* namespace ssvs */
#endif /* GOTO_H_ */
