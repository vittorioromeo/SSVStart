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

namespace ssvs
{
	class GameWindow;
	
	class Game
	{
		typedef std::function<void()> DrawFunc;
		typedef std::function<void(float)> UpdateFunc;
		typedef std::pair<int, DrawFunc> DrawFuncPair;
		friend class GameWindow;

		private:
			GameWindow* gameWindowPtr{nullptr}; // not owned, just pointed to
			std::vector<UpdateFunc> updateFuncs;
			std::multimap<int, DrawFunc> drawFuncsMap;

			Game(const Game&); // non construction-copyable
			Game& operator=(const Game&); // non copyable

		public:
			Game() = default;
			void addUpdateFunc(UpdateFunc);
			void addDrawFunc(DrawFunc, int);
			void update(float);
			void draw();
		};
	} /* namespace ssvs */
#endif /* GAME_H_ */
