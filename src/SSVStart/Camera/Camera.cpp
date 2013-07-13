// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Camera/Camera.h"
#include "SSVStart/Utils/Utils.h"
#include "SSVStart/GameSystem/GameWindow.h"

using namespace sf;
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
}
