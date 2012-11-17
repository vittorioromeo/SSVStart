#include "GameWindow.h"
#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "../Utils.h"

namespace ssvs
{
	GameWindow::GameWindow(unsigned int mScreenWidth, unsigned int mScreenHeight, int mPixelMultiplier, bool mLimitFps, bool mFullscreen) :
			width{mScreenWidth}, height{mScreenHeight}, pixelMultiplier{mPixelMultiplier}
	{
		if(mFullscreen) renderWindow.create(VideoMode{width, height}, "title", Style::Fullscreen);
		else renderWindow.create(VideoMode{width, height}, "title", Style::Default);

		renderWindow.setVerticalSyncEnabled(false);
		if (mLimitFps) renderWindow.setFramerateLimit(60);		
		renderWindow.setSize(Vector2u(width * pixelMultiplier, height * pixelMultiplier));
	}

	void GameWindow::setGame(Game* mGamePtr)
	{
		gamePtr = mGamePtr;
		mGamePtr->gameWindowPtr = this;
	}
	void GameWindow::run()
	{
		while (running)
		{
			renderWindow.setActive(true);
			renderWindow.clear();
			
			runInput();
			runGame();
			
			renderWindow.display();
			
			runFps();
		}
	}
	void GameWindow::stop() { running = false; }
	float GameWindow::getFps() { return fps; }
	
	inline void GameWindow::runGame()
	{
		gamePtr->update(frameTime);
		gamePtr->draw();
	}
	inline void GameWindow::runInput()
	{
		sf::Event event;
		renderWindow.pollEvent(event);
		if (event.type == sf::Event::Closed) running = false; // DEBUG
	}
	inline void GameWindow::runFps()
	{
		if(isFrameTimeStatic) frameTime = staticFrameTime;
		else frameTime = clock.restart().asSeconds() * 60.f;
		
		fps = 60.f / frameTime;
		//renderWindow.setTitle(toStr(fps)); // DEBUG
	}
} /* namespace ssvs */
