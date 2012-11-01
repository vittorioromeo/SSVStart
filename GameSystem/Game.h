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
		typedef std::function<void()> drawFuncType;
		typedef std::function<void(float)> updateFuncType;
		typedef std::pair<int, drawFuncType> updateFuncPair;
		friend class GameWindow;

		private:
			GameWindow* gameWindowPtr { nullptr }; // not owned, just pointed to
			vector<updateFuncType> updateFuncs;
			std::multimap<int, drawFuncType> drawFuncsMap;

			Game(const Game&); // non construction-copyable
			Game& operator=(const Game&); // non copyable
			
		public:
			Game() = default;
			void addUpdateFunc(updateFuncType);
			void addDrawFunc(drawFuncType, int);
			void removeDrawFunc(drawFuncType);
			void update(float);
			void draw();
		};
	} /* namespace ssvs */
#endif /* GAME_H_ */
