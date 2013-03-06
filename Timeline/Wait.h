// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TIMELINE_WAIT
#define SSVS_TIMELINE_WAIT

#include "Command.h"

namespace ssvs
{
	class Wait : public Command
	{
		protected:
			float time, currentTime;
			void update(float mFrameTime) override;
			void reset() override;

		public:
			Wait(Timeline& mTimeline, float mTime);
	};

}
#endif
