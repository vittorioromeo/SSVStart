// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TIMELINE_GO
#define SSVS_TIMELINE_GO

#include "Command.h"

namespace ssvs
{
	class Go : public Command
	{
		protected:
			int targetIndex, times, currentTimes;

			void update(float mFrameTime) override;
			void reset() override;

		public:
			Go(Timeline& mTimeline, int mTargetIndex, int mTimes);
	};
}

#endif
