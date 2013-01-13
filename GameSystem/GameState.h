/* The MIT License (MIT)
 * Copyright (c) 2012 Vittorio Romeo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Input/InputManager.h"

namespace ssvs
{
	class GameWindow;
	
	class GameState
	{
		typedef std::function<void()> DrawFunc;
		typedef std::function<void(float)> UpdateFunc;
		typedef std::pair<int, DrawFunc> DrawFuncPair;
		friend class GameWindow;

		private:
			GameWindow* gameWindowPtr{nullptr}; // not owned, just pointed to
			InputManager inputManager;
			std::vector<UpdateFunc> updateFuncs;
			std::multimap<int, DrawFunc> drawFuncsMap;

		public:
			GameState() = default;
			GameState(const GameState&) = delete; // non construction-copyable
			GameState& operator=(const GameState&) = delete; // non copyable

			void update(float mFrameTime);
			void draw();

			void addInput(InputCombination mInputCombination, InputManager::InputFunc mInputFunc);
			void addUpdateFunc(UpdateFunc);
			void addDrawFunc(DrawFunc, int mPriority = 0);
		};
	} /* namespace ssvs */
#endif /* GAME_H_ */
