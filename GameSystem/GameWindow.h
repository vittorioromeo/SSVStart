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
			unsigned int width, height;
			int pixelMultiplier;
			bool running{true};
			float frameTime{0}, fps{0};
			Game* gamePtr{nullptr}; // not owned, just pointed to
			
			GameWindow(const GameWindow&); // non construction-copyable
			GameWindow& operator=(const GameWindow&); // non copyable
			
			inline void runInput();
			inline void runGame();
			inline void runFps();

		public:
			RenderWindow renderWindow;
			bool isFrameTimeStatic{false};
			float staticFrameTime{1};

			GameWindow(unsigned int mScreenWidth = 320, unsigned int mScreenHeight = 240, int mPixelMultiplier = 1, bool mLimitFps = false, bool mFullscreen = false);

			void setGame(Game*);
			void run();
			void stop();
			float getFps();
	};
} /* namespace ssvs */
#endif /* GAMEWINDOW_H_ */
