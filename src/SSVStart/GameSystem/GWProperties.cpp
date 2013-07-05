// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/GameSystem/GameWindow.h"
#include "SSVStart/GameSystem/GameState.h"
#include "SSVStart/GameSystem/Timers/TimerBase.h"

using namespace sf;

namespace ssvs
{
	void GameWindow::setGameState(GameState& mGameState) 					{ gamePtr = &mGameState; mGameState.gameWindowPtr = this; }
	void GameWindow::setFullscreen(bool mFullscreen) 						{ fullscreen = mFullscreen; mustRecreate = true; }
	void GameWindow::setSize(unsigned int mWidth, unsigned int mHeight) 	{ width = mWidth; height = mHeight; mustRecreate = true; }
	void GameWindow::setAntialiasingLevel(unsigned int mAntialiasingLevel) 	{ antialiasingLevel = mAntialiasingLevel; mustRecreate = true; }
	void GameWindow::setVsync(bool mEnabled)								{ renderWindow.setVerticalSyncEnabled(mEnabled); }
	void GameWindow::setMouseCursorVisible(bool mEnabled) 					{ renderWindow.setMouseCursorVisible(mEnabled); }
	void GameWindow::setTitle(const std::string& mTitle)					{ title = mTitle; renderWindow.setTitle(mTitle); }
	void GameWindow::setFPSLimit(float mFPSLimit)							{ renderWindow.setFramerateLimit(mFPSLimit); }
	RenderWindow& GameWindow::getRenderWindow() 							{ return renderWindow; }
	float GameWindow::getFPS() 												{ return timer.getFps(); }
	bool GameWindow::getFullscreen() 										{ return fullscreen; }
	unsigned int GameWindow::getWidth() 									{ return width; }
	unsigned int GameWindow::getHeight() 									{ return height; }
	unsigned int GameWindow::getAntialiasingLevel() 						{ return antialiasingLevel; }
	sf::Vector2f GameWindow::getMousePosition()								{ return renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow)); }
	bool GameWindow::hasFocus() 											{ return focus; }
}
