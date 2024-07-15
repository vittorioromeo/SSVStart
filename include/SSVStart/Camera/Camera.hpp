// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <cassert>

namespace ssvs {

class GameWindow;

class Camera
{
private:
    sf::View view, computedView;
    sf::Vector2f nextPan, offset, skew{1.f, 1.f};
    float nextZoomFactor{1.f}, nextRotation{0.f};
    bool invalid{true}, mustRecompute{true};

public:
    Camera(const sf::View& mView) : view{mView}
    {}

    Camera(float width, float height, const sf::Vector2f& mCenter,
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

            computedView.setSize(
                {static_cast<T>(computedView.getSize().x * skew.x),
                    static_cast<T>(computedView.getSize().y * skew.y)});

            if(offset.length() != 0)
            {
                computedView.setCenter(
                    view.getCenter() -
                    sf::Vector2f::fromAngle(
                        offset.length(), view.getRotation() + offset.angle()));
            }

            computedView.setCenter({static_cast<T>(computedView.getCenter().x),
                static_cast<T>(computedView.getCenter().y)});

            mustRecompute = false;
        }

        return computedView;
    }

    // These methods change the view ON NEXT UPDATE
    void pan(const sf::Vector2f& mVec)
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

        view.setCenter(view.getCenter() + nextPan);
        view.zoom(std::pow(nextZoomFactor, mFT));
        view.rotate(sf::degrees(nextRotation * mFT));

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
        view.setRotation(sf::degrees(mDeg));
        mustRecompute = true;
    }

    void setSkew(const sf::Vector2f& mSkew) noexcept
    {
        skew = mSkew;
        mustRecompute = true;
    }

    void setOffset(const sf::Vector2f& mOffset) noexcept
    {
        offset = mOffset;
        mustRecompute = true;
    }

    void setCenter(const sf::Vector2f& mPosition) noexcept
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
        return view.getRotation().asDegrees();
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

    auto getMousePosition(const sf::RenderWindow& mRenderWindow) const
    {
        return mRenderWindow.mapPixelToCoords(
            sf::Mouse::getPosition(mRenderWindow), view);
    }

    auto getConvertedCoords(
        const sf::RenderWindow& mRenderWindow, const sf::Vector2i& mPos) const
    {
        return mRenderWindow.mapPixelToCoords(mPos, view);
    }

    bool isInView(const sf::Vector2f& mPos) const
    {
        return mPos.x <= view.getCenter().x + view.getSize().x &&
               (mPos.x >= view.getCenter().x - view.getSize().x &&
                   (mPos.y <= view.getCenter().y + view.getSize().y &&
                       mPos.y >= view.getCenter().y - view.getSize().y));
    }
};

} // namespace ssvs
