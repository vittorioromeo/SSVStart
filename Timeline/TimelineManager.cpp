#include "TimelineManager.h"
#include "Utils/Utils.h"

using namespace ssvs::Utils;

namespace ssvs
{
	TimelineManager::~TimelineManager() { for(auto& timeline : timelines) delete timeline; }
	Timeline& TimelineManager::create() { Timeline* result{new Timeline}; timelines.push_back(result); return *result; }
	void TimelineManager::update(float mFrameTime)
	{
		for(auto& timeline : timelines)
		{
			timeline->update(mFrameTime);
			if(timeline->isFinished()) timelinesToRemove.push_back(timeline);
		}

		for(auto& timelineToRemove : timelinesToRemove)
		{
			eraseRemove(timelines, timelineToRemove);
			delete timelineToRemove;
		}

		timelinesToRemove.clear();
	}
}

