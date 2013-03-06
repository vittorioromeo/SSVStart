#ifndef SSVS_TIMELINE_MANAGER
#define SSVS_TIMELINE_MANAGER

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

#endif 
