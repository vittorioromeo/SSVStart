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
		if(getMagnitude(offset) != 0) computedView.setCenter(view.getCenter() - getVecFromDegrees(view.getRotation() + getDegrees(offset), getMagnitude(offset)));
		renderWindow.setView(computedView);
	}
	void Camera::unapply() { renderWindow.setView(renderWindow.getDefaultView()); }

	void Camera::resize(Vec2f mOffset, Vec2f mSize)
	{
		const auto& size(renderWindow.getSize());
		view = View{{0, 0, mSize.x, mSize.y}};
		view.setViewport({mOffset.x / size.x, mOffset.y / size.y, mSize.x / size.x, mSize.y / size.y});
	}
	void Camera::move(Vec2f mVec) 					{ view.move(mVec); }
	void Camera::zoom(float mFactor) 						{ view.zoom(mFactor); }
	void Camera::centerOn(Vec2f mPosition) 				{ view.setCenter(mPosition); }
	void Camera::rotate(float mAngle)						{ view.rotate(mAngle); }

	void Camera::setView(const View& mView) 				{ view = mView; }
	void Camera::setRotation(float mAngle)					{ view.setRotation(mAngle); }
	void Camera::setSkew(Vec2f mSkew)					{ skew = mSkew; }
	void Camera::setOffset(Vec2f mOffset)				{ offset = mOffset; }

	View Camera::getView() const									{ return view; }
	float Camera::getRotation() const								{ return view.getRotation(); }
	Vec2f Camera::getSkew() const								{ return skew; }
	Vec2f Camera::getOffset() const								{ return offset; }
	Vec2f Camera::getCenter() const								{ return view.getCenter(); }
	Vec2f Camera::getMousePosition() const						{ return renderWindow.mapPixelToCoords({Mouse::getPosition(renderWindow)}, view); }
	Vec2f Camera::getConvertedCoords(Vec2i mPosition) const	{ return renderWindow.mapPixelToCoords(mPosition, view); }
	bool Camera::isInView(Vec2f mPosition) const
	{
		return mPosition.x <= view.getCenter().x + view.getSize().x && (mPosition.x >= view.getCenter().x - view.getSize().x &&
			(mPosition.y <= view.getCenter().y + view.getSize().y && mPosition.y >= view.getCenter().y - view.getSize().y));
	}
}
