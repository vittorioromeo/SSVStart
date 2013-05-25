// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_CAMERA
#define SSVS_CAMERA

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace ssvs
{
	class GameWindow;

	class Camera
	{
		private:
			GameWindow& gameWindow;
			sf::RenderWindow& renderWindow;
			sf::View view;
			sf::Vector2f skew{1, 1}, offset{0, 0};

		public:
			Camera(GameWindow& mGameWindow, sf::View mView);

			void apply();
			void unapply();

			void resize(sf::Vector2f mOffset, sf::Vector2f mSize);
			void move(sf::Vector2f mVector);
			void zoom(float mFactor);
			void centerOn(sf::Vector2f mPosition);
			void rotate(float mAngle);

			void setView(sf::View mView);
			void setRotation(float mAngle);
			void setSkew(sf::Vector2f mSkew);
			void setOffset(sf::Vector2f mOffset);

			sf::View getView() const;
			float getRotation() const;
			sf::Vector2f getSkew() const;
			sf::Vector2f getOffset() const;
			sf::Vector2f getCenter() const;
			sf::Vector2f getMousePosition() const;
			sf::Vector2f getConvertedCoords(sf::Vector2i mPosition) const;
			bool isInView(sf::Vector2f mPosition) const;
	};
}

#endif
