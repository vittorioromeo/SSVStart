#ifndef SSVS_INPUT_MANAGER
#define SSVS_INPUT_MANAGER

#include <vector>
#include <functional>
#include <SFML/Window.hpp>

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Trigger;

		class Manager
		{
			public:
				typedef std::function<void(float)> InputFunc;
				typedef std::pair<Trigger, InputFunc> InputFuncPair;

			private:
				std::vector<InputFuncPair> inputFuncPairs;

			public:
				void addInput(Trigger mInputCombination, InputFunc mInputFunc);
				void update(GameWindow& mGameWindow, float mFrameTime);
		};
	}
}

#endif
