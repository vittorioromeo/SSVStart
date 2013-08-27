// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_CAMERA
#define SSVS_CAMERA

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.h"
#include "SSVStart/Utils/Utils.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	class GameWindow;

	class Camera
	{
		private:
			GameWindow& gameWindow;
			sf::RenderWindow& renderWindow;
			sf::View view, computedView;
			bool invalid{true}, mustRecompute{true};
			Vec2f nextPan, offset, skew{1.f, 1.f};
			float nextZoomFactor{1.f}, nextRotation{0.f};

		public:
			Camera(GameWindow& mGameWindow, const sf::View& mView) : gameWindow(mGameWindow), renderWindow(gameWindow.getRenderWindow()), view{mView} { }

			Camera(GameWindow& mGameWindow, const Vec2f& mCenter, float mZoomFactor = 1.f)
				: gameWindow(mGameWindow), renderWindow(gameWindow.getRenderWindow()), view{mCenter, {gameWindow.getWidth() / mZoomFactor, gameWindow.getHeight() / mZoomFactor}} { }

			Camera(GameWindow& mGameWindow, float mZoomFactor = 1.f) : gameWindow(mGameWindow), renderWindow(gameWindow.getRenderWindow()),
				view{{gameWindow.getWidth() / 2.f / mZoomFactor, gameWindow.getHeight() / 2.f / mZoomFactor}, {gameWindow.getWidth() / mZoomFactor, gameWindow.getHeight() / mZoomFactor}} { }

			template<typename T = float> inline void apply()
			{
				if(mustRecompute)
				{
					computedView = view;
					computedView.setSize(static_cast<T>(computedView.getSize().x * skew.x), static_cast<T>(computedView.getSize().y * skew.y));
					if(getMagnitude(offset) != 0) computedView.setCenter(view.getCenter() - getVecFromDegrees(view.getRotation() + getDegrees(offset), getMagnitude(offset)));
					computedView.setCenter(static_cast<T>(computedView.getCenter().x), static_cast<T>(computedView.getCenter().y));
				}

				renderWindow.setView(computedView);
			}
			inline void unapply() { renderWindow.setView(renderWindow.getDefaultView()); }

			// These methods change the view ON NEXT UPDATE
			inline void pan(const Vec2f& mVec)	{ nextPan += mVec;					invalid = true; }
			inline void pan(float mX, float mY)	{ nextPan.x += mX; nextPan.y += mY;	invalid = true; }
			inline void zoomIn(float mFactor)	{ nextZoomFactor /= mFactor;		invalid = true; }
			inline void zoomOut(float mFactor)	{ nextZoomFactor *= mFactor;		invalid = true; }
			inline void turn(float mDegrees)	{ nextRotation += mDegrees;			invalid = true; }

			template<typename T = float> inline void update(float mFrameTime)
			{
				if(!invalid) return;

				view.setCenter(view.getCenter() + nextPan);
				view.zoom(std::pow(nextZoomFactor, mFrameTime));
				view.rotate(nextRotation * mFrameTime);

				mustRecompute = true;
				nullify(nextPan);
				nextZoomFactor = 1.f;
				nextRotation = 0.f;
				invalid = false;
			}

			// These properties IMMEDIATELY change the view
			inline void setView(const sf::View& mView)		{ view = mView;					mustRecompute = true; }
			inline void setRotation(float mDegrees)			{ view.setRotation(mDegrees);	mustRecompute = true; }
			inline void setSkew(const Vec2f& mSkew)			{ skew = mSkew;					mustRecompute = true; }
			inline void setOffset(const Vec2f& mOffset)		{ offset = mOffset;				mustRecompute = true; }
			inline void setCenter(const Vec2f& mPosition) 	{ view.setCenter(mPosition);	mustRecompute = true; }

			// This property changes the view ON NEXT UPDATE
			inline void setNextZoomFactor(float mFactor)	{ nextZoomFactor = mFactor;		invalid = true; }

			inline const sf::View& getView() const			{ return view; }
			inline float getRotation() const				{ return view.getRotation(); }
			inline const Vec2f& getSkew() const				{ return skew; }
			inline const Vec2f& getOffset() const			{ return offset; }
			inline const Vec2f& getCenter() const			{ return view.getCenter(); }
			inline float getNextZoomFactor() const			{ return nextZoomFactor; }

			inline Vec2f getMousePosition() const						{ return renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow), view); }
			inline Vec2f getConvertedCoords(const Vec2i& mPos) const	{ return renderWindow.mapPixelToCoords(mPos, view); }
			inline bool isInView(const Vec2f& mPos) const
			{
				return mPos.x <= view.getCenter().x + view.getSize().x && (mPos.x >= view.getCenter().x - view.getSize().x &&
					(mPos.y <= view.getCenter().y + view.getSize().y && mPos.y >= view.getCenter().y - view.getSize().y));
			}
	};
}

#endif
