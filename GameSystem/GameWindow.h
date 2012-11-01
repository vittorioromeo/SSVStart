#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

namespace ssvs
{
	class Game;
	
	class GameWindow
	{
		private:
			Clock clock;
			int width, height, pixelMultiplier;
			bool running { true };
			float frameTime { 0 }, fps { 0 };
			Game* gamePtr { nullptr }; // not owned, just pointed to
			
			GameWindow(const GameWindow&); // non construction-copyable
			GameWindow& operator=(const GameWindow&); // non copyable
			
			inline void runInput();
			inline void runGame();
			inline void runFps();

		public:
			RenderWindow renderWindow;
			
			GameWindow(int, int, int, bool);

			void setGame(Game*);
			void run();
			float getFps();
	};
} /* namespace ssvs */
#endif /* GAMEWINDOW_H_ */
