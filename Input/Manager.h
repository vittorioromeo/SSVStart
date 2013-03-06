#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Input/Trigger.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
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

#endif // INPUTMANAGER_H
