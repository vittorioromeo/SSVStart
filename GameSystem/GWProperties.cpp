#include "GameWindow.h"

namespace ssvs
{
	void GameWindow::setGame(Game* mGamePtr)
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
	float GameWindow::getFps() { return fps; }
	bool GameWindow::getFullscreen() { return fullscreen; }
	unsigned int GameWindow::getWidth() { return width; }
	unsigned int GameWindow::getHeight() { return height; }
	bool GameWindow::isKeyPressed(Keyboard::Key mKey) { return hasFocus && Keyboard::isKeyPressed(mKey); }
	void GameWindow::setStaticFrameTime(bool mEnabled) { staticFrameTime = mEnabled; }
	void GameWindow::setVsync(bool mEnabled) { renderWindow.setVerticalSyncEnabled(mEnabled); }
	void GameWindow::setMouseCursorVisible(bool mEnabled) { renderWindow.setMouseCursorVisible(mEnabled); }
	void GameWindow::setStaticFrameTimeValue(float mValue) { staticFrameTimeValue = mValue; }
}
