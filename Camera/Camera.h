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
			Camera(GameWindow& mGameWindow, float mWidth, float mHeight);

			void apply();
			void unapply();
			sf::Vector2f getMousePosition();
			sf::Vector2f getConvertedCoords(int mX, int mY);
			void resize(float mXOffset, float mYOffset, float mWidth, float mHeight);
			bool isInView(sf::Vector2f mPosition);
			void move(sf::Vector2f mVector);
			void zoom(float mFactor);
			void centerOn(sf::Vector2f mPosition);
			void rotate(float mAngle);
	};
}

#endif // CAMERA_H
