#include "Camera.h"

using namespace sf;

namespace ssvs
{
	Camera::Camera(GameWindow& mGameWindow, View mView) : gameWindow(mGameWindow), renderWindow(gameWindow.getRenderWindow()), view{mView} { }

	void Camera::apply() 	{ renderWindow.setView(view); }
	void Camera::unapply() 	{ renderWindow.setView(renderWindow.getDefaultView()); }

	void Camera::resize(Vector2f mOffset, Vector2f mSize)
	{
		auto size = renderWindow.getSize(); view = View{{0, 0, mSize.x, mSize.y}};
		view.setViewport({mOffset.x / size.x, mOffset.y / size.y, mSize.x / size.x, mSize.y / size.y});
	}	
	void Camera::move(Vector2f mVector) 		{ view.move(mVector); }
	void Camera::zoom(float mFactor) 			{ view.zoom(mFactor); }
	void Camera::centerOn(Vector2f mPosition) 	{ view.setCenter(mPosition); }
	void Camera::rotate(float mAngle)			{ view.rotate(mAngle); }

	void Camera::setView(sf::View mView) 		{ view = mView; }
	void Camera::setRotation(float mAngle)		{ view.setRotation(mAngle); }

	sf::View Camera::getView() { return view; }
	float Camera::getRotation() { return view.getRotation(); }
	sf::Vector2f Camera::getCenter() { return view.getCenter(); }
	Vector2f Camera::getMousePosition() { return renderWindow.mapPixelToCoords({Mouse::getPosition(renderWindow)}, view); }
	Vector2f Camera::getConvertedCoords(Vector2i mPosition) { return renderWindow.mapPixelToCoords(mPosition, view); }
	bool Camera::isInView(Vector2f mPosition)
	{
		return mPosition.x <= view.getCenter().x + view.getSize().x && (mPosition.x >= view.getCenter().x - view.getSize().x &&
			(mPosition.y <= view.getCenter().y + view.getSize().y && mPosition.y >= view.getCenter().y - view.getSize().y));
	}
}
