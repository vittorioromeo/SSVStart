// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_CAMERA
#define SSVS_CAMERA

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class GameWindow;

	class Camera
	{
		private:
			GameWindow& gameWindow;
			sf::RenderWindow& renderWindow;
			sf::View view;
			Vec2f skew{1, 1}, offset{0, 0};

		public:
			Camera(GameWindow& mGameWindow, sf::View mView);

			void apply();
			void unapply();

			void resize(Vec2f mOffset, Vec2f mSize);
			void move(Vec2f mVec);
			void zoom(float mFactor);
			void centerOn(Vec2f mPosition);
			void rotate(float mAngle);

			void setView(const sf::View& mView);
			void setRotation(float mAngle);
			void setSkew(Vec2f mSkew);
			void setOffset(Vec2f mOffset);

			sf::View getView() const;
			float getRotation() const;
			Vec2f getSkew() const;
			Vec2f getOffset() const;
			Vec2f getCenter() const;
			Vec2f getMousePosition() const;
			Vec2f getConvertedCoords(Vec2i mPosition) const;
			bool isInView(Vec2f mPosition) const;
	};
}

#endif
