// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Utils/Vector2.hpp"
#include "SSVStart/GameSystem/GameSystem.hpp"

#include <cassert>

namespace ssvs
{

class GameWindow;

class Camera
{
private:
    GameWindow& gameWindow;
    sf::RenderWindow& renderWindow;
    sf::View view, computedView;
    Vec2f nextPan, offset, skew{1.f, 1.f};
    float nextZoomFactor{1.f}, nextRotation{0.f};
    bool invalid{true}, mustRecompute{true};

public:
    Camera(GameWindow& mGameWindow, const sf::View& mView)
        : gameWindow(mGameWindow), renderWindow(gameWindow), view{mView}
    {
    }

    Camera(
        GameWindow& mGameWindow, const Vec2f& mCenter, float mZoomFactor = 1.f)
        : gameWindow(mGameWindow),
          renderWindow(gameWindow), view{mCenter,
                                        {gameWindow.getWidth() / mZoomFactor,
                                            gameWindow.getHeight() /
                                                mZoomFactor}}
    {
        assert(mZoomFactor != 0);
    }

    Camera(GameWindow& mGameWindow, float mZoomFactor = 1.f)
        : gameWindow(mGameWindow), renderWindow(gameWindow),
          view{{gameWindow.getWidth() / 2.f / mZoomFactor,
                   gameWindow.getHeight() / 2.f / mZoomFactor},
              {gameWindow.getWidth() / mZoomFactor,
                  gameWindow.getHeight() / mZoomFactor}}
    {
        assert(mZoomFactor != 0);
    }

    template <typename T = float>
    void apply()
    {
        if(mustRecompute)
        {
            computedView = view;
            computedView.setSize(toNum<T>(computedView.getSize().x * skew.x),
                toNum<T>(computedView.getSize().y * skew.y));
            if(getMag(offset) != 0)
                computedView.setCenter(
                    view.getCenter() -
                    getVecFromDeg(
                        view.getRotation() + getDeg(offset), getMag(offset)));
            computedView.setCenter(toNum<T>(computedView.getCenter().x),
                toNum<T>(computedView.getCenter().y));
            mustRecompute = false;
        }

        renderWindow.setView(computedView);
    }
    void unapply()
    {
        renderWindow.setView(renderWindow.getDefaultView());
    }

    // These methods change the view ON NEXT UPDATE
    void pan(const Vec2f& mVec)
    {
        nextPan += mVec;
        invalid = true;
    }
    void pan(float mX, float mY)
    {
        nextPan.x += mX;
        nextPan.y += mY;
        invalid = true;
    }
    void zoomIn(float mFactor)
    {
        nextZoomFactor /= mFactor;
        invalid = true;
    }
    void zoomOut(float mFactor)
    {
        nextZoomFactor *= mFactor;
        invalid = true;
    }
    void turn(float mDeg)
    {
        nextRotation += mDeg;
        invalid = true;
    }

    template <typename T = float>
    void update(FT mFT)
    {
        if(!invalid) return;

        view.setCenter(view.getCenter() + nextPan);
        view.zoom(std::pow(nextZoomFactor, mFT));
        view.rotate(nextRotation * mFT);

        mustRecompute = true;
        nullify(nextPan);
        nextZoomFactor = 1.f;
        nextRotation = 0.f;
        invalid = false;
    }

    // These properties IMMEDIATELY change the view
    void setView(const sf::View& mView) noexcept
    {
        view = mView;
        mustRecompute = true;
    }
    void setRotation(float mDeg) noexcept
    {
        view.setRotation(mDeg);
        mustRecompute = true;
    }
    void setSkew(const Vec2f& mSkew) noexcept
    {
        skew = mSkew;
        mustRecompute = true;
    }
    void setOffset(const Vec2f& mOffset) noexcept
    {
        offset = mOffset;
        mustRecompute = true;
    }
    void setCenter(const Vec2f& mPosition) noexcept
    {
        view.setCenter(mPosition);
        mustRecompute = true;
    }

    // This property changes the view ON NEXT UPDATE
    void setNextZoomFactor(float mFactor) noexcept
    {
        nextZoomFactor = mFactor;
        invalid = true;
    }

    const auto& getView() const noexcept
    {
        return view;
    }
    float getRotation() const noexcept
    {
        return view.getRotation();
    }
    const auto& getSkew() const noexcept
    {
        return skew;
    }
    const auto& getOffset() const noexcept
    {
        return offset;
    }
    const auto& getCenter() const noexcept
    {
        return view.getCenter();
    }
    float getNextZoomFactor() const noexcept
    {
        return nextZoomFactor;
    }

    auto getMousePosition() const
    {
        return renderWindow.mapPixelToCoords(
            sf::Mouse::getPosition(renderWindow), view);
    }
    auto getConvertedCoords(const Vec2i& mPos) const
    {
        return renderWindow.mapPixelToCoords(mPos, view);
    }
    bool isInView(const Vec2f& mPos) const
    {
        return mPos.x <= view.getCenter().x + view.getSize().x &&
               (mPos.x >= view.getCenter().x - view.getSize().x &&
                   (mPos.y <= view.getCenter().y + view.getSize().y &&
                       mPos.y >= view.getCenter().y - view.getSize().y));
    }
};

} // namespace ssvs
