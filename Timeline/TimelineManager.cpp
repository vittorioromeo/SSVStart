#include "TimelineManager.h"
#include "Utils/Utils.h"

using namespace ssvs::Utils;

namespace ssvs
{
	Timeline& TimelineManager::create() { return memoryManager.create(); }
	void TimelineManager::update(float mFrameTime)
	{
		for(auto& t : memoryManager.getItems()) { t->update(mFrameTime); if(t->isFinished()) memoryManager.del(t); }
		memoryManager.cleanUp();
	}
	void TimelineManager::clear() { memoryManager.clear(); }
}
