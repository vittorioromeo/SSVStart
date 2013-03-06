// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TIMELINE_DO
#define SSVS_TIMELINE_DO

#include "Command.h"
#include <functional>

namespace ssvs
{
	class Do : public Command
	{
		typedef std::function<void()> Action;

		protected:
			Action action;
			void update(float mFrameTime) override;

		public:
			Do(Timeline& mTimeline, Action mAction);
	};
}

#endif
