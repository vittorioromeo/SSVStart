#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../GameSystem/GameWindow.h"
#include "InputCombination.h"

namespace ssvs
{
	class InputManager
	{
		public:
			typedef std::function<void(float)> InputFunc;
			typedef std::pair<InputCombination, InputFunc> InputFuncPair;
			void addInput(InputCombination mInputCombination, InputFunc mInputFunc);
			void update(GameWindow& mGameWindow, float mFrameTime);

		private:
			std::vector<InputFuncPair> inputFuncPairs;
	};
}

#endif // INPUTMANAGER_H
