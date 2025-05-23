// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include <SFML/System/Vec2.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <SFML/Window/Mouse.hpp>

#include <cassert>
#include <cmath>

namespace ssvs {

class GameWindow;

class Camera
{
private:
    sf::View view, computedView;
    sf::Vec2f nextPan, offset, skew{1.f, 1.f};
    float nextZoomFactor{1.f}, nextRotation{0.f};
    bool invalid{true}, mustRecompute{true};

public:
    Camera(const sf::View& mView) : view{mView}
    {}

    Camera(float width, float height, const sf::Vec2f& mCenter,
        float mZoomFactor = 1.f)
        : view{mCenter, {width / mZoomFactor, height / mZoomFactor}}
    {
        assert(mZoomFactor != 0);
    }

    Camera(float width, float height, float mZoomFactor = 1.f)
        : view{{width / 2.f / mZoomFactor, height / 2.f / mZoomFactor},
              {width / mZoomFactor, height / mZoomFactor}}
    {
        assert(mZoomFactor != 0);
    }

    template <typename T = float>
    [[nodiscard]] sf::View apply()
    {
        if(mustRecompute)
        {
            computedView = view;

            computedView.size = {static_cast<T>(computedView.size.x * skew.x),
                static_cast<T>(computedView.size.y * skew.y)};

            if(offset.length() != 0)
            {
                computedView.center =
                    (view.center - sf::Vec2f::fromAngle(offset.length(),
                                       view.rotation + offset.angle()));
            }

            computedView.center = {static_cast<T>(computedView.center.x),
                static_cast<T>(computedView.center.y)};

            mustRecompute = false;
        }

        return computedView;
    }

    // These methods change the view ON NEXT UPDATE
    void pan(const sf::Vec2f& mVec)
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
    void update(float mFT)
    {
        if(!invalid) return;

        view.center = view.center + nextPan;
        view.size *= std::pow(nextZoomFactor, mFT);
        view.rotation += sf::degrees(nextRotation * mFT);

        mustRecompute = true;
        nextPan = {0.f, 0.f};
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
        view.rotation = sf::degrees(mDeg);
        mustRecompute = true;
    }

    void setSkew(const sf::Vec2f& mSkew) noexcept
    {
        skew = mSkew;
        mustRecompute = true;
    }

    void setOffset(const sf::Vec2f& mOffset) noexcept
    {
        offset = mOffset;
        mustRecompute = true;
    }

    void setCenter(const sf::Vec2f& mPosition) noexcept
    {
        view.center = mPosition;
        mustRecompute = true;
    }

    // This property changes the view ON NEXT UPDATE
    void setNextZoomFactor(float mFactor) noexcept
    {
        nextZoomFactor = mFactor;
        invalid = true;
    }

    const sf::View& getView() const noexcept
    {
        return view;
    }

    float getRotation() const noexcept
    {
        return view.rotation.asDegrees();
    }

    const sf::Vec2f& getSkew() const noexcept
    {
        return skew;
    }

    const sf::Vec2f& getOffset() const noexcept
    {
        return offset;
    }

    sf::Vec2f getCenter() const noexcept
    {
        return view.center;
    }

    float getNextZoomFactor() const noexcept
    {
        return nextZoomFactor;
    }

    sf::Vec2f getMousePosition(const sf::RenderWindow& mRenderWindow) const
    {
        return mRenderWindow.mapPixelToCoords(
            sf::Mouse::getPosition(mRenderWindow), view);
    }

    sf::Vec2f getConvertedCoords(
        const sf::RenderWindow& mRenderWindow, const sf::Vec2i& mPos) const
    {
        return mRenderWindow.mapPixelToCoords(mPos, view);
    }

    bool isInView(const sf::Vec2f& mPos) const
    {
        return mPos.x <= view.center.x + view.size.x &&
               (mPos.x >= view.center.x - view.size.x &&
                   (mPos.y <= view.center.y + view.size.y &&
                       mPos.y >= view.center.y - view.size.y));
    }
};

} // namespace ssvs
