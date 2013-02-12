#ifndef TIMELINEMANAGER_H
#define TIMELINEMANAGER_H

#include "Timeline.h"

namespace ssvs
{

	class TimelineManager
	{
		private:
			std::vector<Timeline*> timelines; // owned
			std::vector<Timeline*> timelinesToRemove;

		public:
			TimelineManager() = default;
			~TimelineManager();

			Timeline& create();
			void update(float mFrameTime);
			void clear();
};

}

#endif // TIMELINEMANAGER_H
