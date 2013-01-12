#include "GameWindow.h"
#include "GameState.h"

using namespace sf;

namespace ssvs
{
	void GameWindow::setGame(GameState* mGamePtr)
	{
		gamePtr = mGamePtr;
		mGamePtr->gameWindowPtr = this;
	}
	void GameWindow::setFullscreen(bool mFullscreen)
	{
		fullscreen = mFullscreen;

		renderWindow.close();
		recreateWindow();
	}
	void GameWindow::setSize(unsigned int mWidth, unsigned int mHeight)
	{
		width = mWidth;
		height = mHeight;

		renderWindow.close();
		recreateWindow();
	}
	RenderWindow& GameWindow::getRenderWindow() 			{ return renderWindow; }
	float GameWindow::getFps() 								{ return fps; }
	bool GameWindow::getFullscreen() 						{ return fullscreen; }
	unsigned int GameWindow::getWidth() 					{ return width; }
	unsigned int GameWindow::getHeight() 					{ return height; }
	sf::Vector2f GameWindow::getMousePosition()				{ return renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow)); }
	void GameWindow::setStaticFrameTime(bool mEnabled) 		{ staticFrameTime = mEnabled; }
	void GameWindow::setVsync(bool mEnabled)				{ renderWindow.setVerticalSyncEnabled(mEnabled); }
	void GameWindow::setMouseCursorVisible(bool mEnabled) 	{ renderWindow.setMouseCursorVisible(mEnabled); }
	void GameWindow::setStaticFrameTimeValue(float mValue) 	{ staticFrameTimeValue = mValue; }
	void GameWindow::setTitle(const std::string& mTitle)	{ renderWindow.setTitle(mTitle); }
}
