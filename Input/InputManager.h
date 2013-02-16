#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "InputCombo.h"

namespace ssvs
{
	class GameWindow;

	class InputManager
	{
		public:
			typedef std::function<void(float)> InputFunc;
			typedef std::pair<InputCombo, InputFunc> InputFuncPair;

		private:
			std::vector<InputFuncPair> inputFuncPairs;

		public:
			void addInput(InputCombo mInputCombination, InputFunc mInputFunc);
			void update(GameWindow& mGameWindow, float mFrameTime);
	};
}

#endif // INPUTMANAGER_H
