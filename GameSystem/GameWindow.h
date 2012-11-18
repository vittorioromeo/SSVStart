#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace ssvs
{
	class Game;
	
	class GameWindow
	{
		private:
			Game* gamePtr{nullptr}; // not owned, just pointed to
			Clock clock;
			string title{""};
			unsigned int width, height;
			int pixelMultiplier;
			bool isFullscreen;
			float frameTime{0};
			float fps{0};
			bool running{true};
			bool hasFocus{true};
			
			GameWindow(const GameWindow&); // non construction-copyable
			GameWindow& operator=(const GameWindow&); // non copyable
			
			inline void runInput();
			inline void runGame();
			inline void runFps();

		public:
			RenderWindow renderWindow;
			bool isFrameTimeStatic{false};
			float staticFrameTime{1};

			GameWindow(string mTitle, unsigned int mScreenWidth = 320, unsigned int mScreenHeight = 240, int mPixelMultiplier = 1, bool mLimitFps = false, bool mFullscreen = false);

			void setGame(Game*);
			void run();
			void stop();
			float getFps();
			bool isKeyPressed(Keyboard::Key mKey);
			bool getFullscreen();
			void setFullscreen(bool mFullscreen);
			void recreateWindow();

			void setSize(unsigned int mWidth, unsigned int mHeight);
			unsigned int getWidth();
			unsigned int getHeight();
	};
} /* namespace ssvs */
#endif /* GAMEWINDOW_H_ */
