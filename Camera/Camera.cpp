#include "Camera.h"

using namespace sf;

namespace ssvs
{
	Camera::Camera(GameWindow& mGameWindow, float mWidth, float mHeight) : gameWindow(mGameWindow), renderWindow(gameWindow.getRenderWindow()), view{{0, 0, mWidth, mHeight}} { }

	void Camera::apply() { renderWindow.setView(view); }
	void Camera::unapply() { renderWindow.setView(renderWindow.getDefaultView()); }
	Vector2f Camera::getMousePosition()
	{
		Vector2i mPos{Mouse::getPosition(renderWindow)};
		return renderWindow.mapPixelToCoords({mPos.x, mPos.y}, view);
	}
	Vector2f Camera::getConvertedCoords(int mX, int mY) { return renderWindow.mapPixelToCoords({mX, mY}, view); }
	void Camera::resize(float mXOffset, float mYOffset, float mWidth, float mHeight)
	{
		auto size = renderWindow.getSize();
		view = View{{0, 0, mWidth, mHeight}};
		view.setViewport({mXOffset / size.x, mYOffset / size.y, mWidth / size.x, mHeight / size.y});
	}
	bool Camera::isInView(Vector2f mPosition)
	{
		return mPosition.x <= view.getCenter().x + view.getSize().x && (mPosition.x >= view.getCenter().x - view.getSize().x &&
				(mPosition.y <= view.getCenter().y + view.getSize().y && mPosition.y >= view.getCenter().y - view.getSize().y));
	}
	void Camera::move(Vector2f mVector) 		{ view.move(mVector); }
	void Camera::zoom(float mFactor) 			{ view.zoom(mFactor); }
	void Camera::centerOn(Vector2f mPosition) 	{ view.setCenter(mPosition); }
	void Camera::rotate(float mAngle)			{ view.rotate(mAngle); }
}
