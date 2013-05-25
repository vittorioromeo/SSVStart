#include <SFML/Graphics.hpp>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Animation/Animation.h"

using namespace std;
using namespace sf;
using namespace ssvu;

namespace ssvs
{
	void Animation::nextStep()
	{
		int lastIndex{currentIndex};
		reverse ? --currentIndex : ++currentIndex;

		if(currentIndex >= static_cast<int>(steps.size()))
		{
			if(loop)
			{
				if(pingPong) { reverse = !reverse; currentIndex = lastIndex; }
				else currentIndex = 0;
			}
			else currentIndex = lastIndex;
		}
		else if(currentIndex < 0)
		{
			if(loop)
			{
				if(pingPong) { reverse = !reverse; currentIndex = lastIndex; }
				else currentIndex = steps.size() - 1;
			}
			else currentIndex = lastIndex;
		}

		currentTime = 0;
	}

	void Animation::update(float mFrameTime)
	{
		if(steps.empty()) return;

		currentTime += mFrameTime * speed;
		if(currentTime >= getCurrentStep().time) nextStep();
	}

	void Animation::addStep(AnimationStep mStep)								{ steps.push_back(mStep); }
	void Animation::addSteps(std::vector<AnimationStep> mSteps)					{ for(const auto& step : mSteps) steps.push_back(step); }
	void Animation::addSteps(std::vector<string> mStepLabels, float mStepTime)	{ for(const auto& label : mStepLabels) steps.push_back({label, mStepTime}); }

	// Getters
	const AnimationStep& Animation::getCurrentStep() const { return steps[currentIndex]; }
	const string& Animation::getCurrentLabel() const { return getCurrentStep().label; }

	// Setters
	void Animation::setSpeed(float mSpeed)		{ speed = mSpeed; }
	void Animation::setLoop(bool mLoop)			{ loop = mLoop; }
	void Animation::setPingPong(bool mPingPong)	{ pingPong = mPingPong; }
	void Animation::setReverse(bool mReverse)	{ reverse = mReverse; }
}
