// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TIMELINE_COMMAND
#define SSVS_TIMELINE_COMMAND

namespace ssvs
{
	class Timeline;

	struct Command
	{
		Timeline& timeline;

		Command(Timeline& mTimeline);
		virtual ~Command();
		virtual void update(float mFrameTime);
		virtual void reset();
	};
}
#endif
