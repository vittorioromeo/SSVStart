#ifndef TIMELINEMANAGER_H
#define TIMELINEMANAGER_H

#include "Timeline.h"
#include "Utils/MemoryManager.h"

namespace ssvs
{
	class TimelineManager
	{
		private:
			Utils::MemoryManager<Timeline> memoryManager;

		public:
			TimelineManager() = default;

			Timeline& create();
			void update(float mFrameTime);
			void clear();
	};
}

#endif // TIMELINEMANAGER_H
