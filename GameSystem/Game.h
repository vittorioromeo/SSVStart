#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>
#include <functional>
#include <map>

using namespace std;

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
			GameWindow* gameWindowPtr { nullptr }; // not owned, just pointed to
			vector<UpdateFunc> updateFuncs;
			multimap<int, DrawFunc> drawFuncsMap;

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
