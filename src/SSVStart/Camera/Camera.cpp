// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Camera/Camera.h"
#include "SSVStart/Utils/Utils.h"
#include "SSVStart/GameSystem/GameWindow.h"

using namespace sf;
using namespace ssvu;
using namespace ssvs::Utils;

namespace ssvs
{
	Camera::Camera(GameWindow& mGameWindow, View mView) : gameWindow(mGameWindow), renderWindow(gameWindow.getRenderWindow()), view{mView} { }

	void Camera::apply()
	{
		View computedView{view};
		computedView.setSize(computedView.getSize().x * skew.x, computedView.getSize().y * skew.y);
		if(getMagnitude(offset) != 0) computedView.setCenter(view.getCenter() - getVectorFromDegrees(view.getRotation() + getDegrees(offset), getMagnitude(offset)));
		renderWindow.setView(computedView);
	}
	void Camera::unapply() { renderWindow.setView(renderWindow.getDefaultView()); }

	void Camera::resize(Vector2f mOffset, Vector2f mSize)
	{
		auto size(renderWindow.getSize());
		view = View{{0, 0, mSize.x, mSize.y}};
		view.setViewport({mOffset.x / size.x, mOffset.y / size.y, mSize.x / size.x, mSize.y / size.y});
	}
	void Camera::move(Vector2f mVector) 					{ view.move(mVector); }
	void Camera::zoom(float mFactor) 						{ view.zoom(mFactor); }
	void Camera::centerOn(Vector2f mPosition) 				{ view.setCenter(mPosition); }
	void Camera::rotate(float mAngle)						{ view.rotate(mAngle); }

	void Camera::setView(View mView) 						{ view = mView; }
	void Camera::setRotation(float mAngle)					{ view.setRotation(mAngle); }
	void Camera::setSkew(Vector2f mSkew)					{ skew = mSkew; }
	void Camera::setOffset(Vector2f mOffset)				{ offset = mOffset; }

	View Camera::getView() const									{ return view; }
	float Camera::getRotation() const								{ return view.getRotation(); }
	Vector2f Camera::getSkew() const								{ return skew; }
	Vector2f Camera::getOffset() const								{ return offset; }
	Vector2f Camera::getCenter() const								{ return view.getCenter(); }
	Vector2f Camera::getMousePosition() const						{ return renderWindow.mapPixelToCoords({Mouse::getPosition(renderWindow)}, view); }
	Vector2f Camera::getConvertedCoords(Vector2i mPosition) const	{ return renderWindow.mapPixelToCoords(mPosition, view); }
	bool Camera::isInView(Vector2f mPosition) const
	{
		return mPosition.x <= view.getCenter().x + view.getSize().x && (mPosition.x >= view.getCenter().x - view.getSize().x &&
			(mPosition.y <= view.getCenter().y + view.getSize().y && mPosition.y >= view.getCenter().y - view.getSize().y));
	}
}
