#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../GameSystem/GameWindow.h"

namespace ssvs
{
	class Camera
	{
		private:
			GameWindow& gameWindow;
			sf::RenderWindow& renderWindow;
			sf::View view;

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

			sf::View getView();
			sf::Vector2f getCenter();
			sf::Vector2f getMousePosition();
			sf::Vector2f getConvertedCoords(sf::Vector2i mPosition);
			bool isInView(sf::Vector2f mPosition);
	};
}

#endif // CAMERA_H
