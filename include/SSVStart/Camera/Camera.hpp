// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Utils/Vector2.hpp"
#include "SSVStart/GameSystem/GameSystem.hpp"

#include <SSVUtils/Core/Common/Casts.hpp>

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <cassert>

namespace ssvs
{

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
    {
    }

    Camera(GameWindow& mGameWindow, const sf::Vector2f& mCenter,
        float mZoomFactor = 1.f)
        : view{mCenter, {mGameWindow.getWidth() / mZoomFactor,
                            mGameWindow.getHeight() / mZoomFactor}}
    {
        assert(mZoomFactor != 0);
    }

    Camera(GameWindow& mGameWindow, float mZoomFactor = 1.f)
        : view{{mGameWindow.getWidth() / 2.f / mZoomFactor,
                   mGameWindow.getHeight() / 2.f / mZoomFactor},
              {mGameWindow.getWidth() / mZoomFactor,
                  mGameWindow.getHeight() / mZoomFactor}}
    {
        assert(mZoomFactor != 0);
    }

    template <typename T = float>
    void apply(sf::RenderTarget& mRenderTarget)
    {
        if(mustRecompute)
        {
            computedView = view;
            computedView.setSize(
                ssvu::toNum<T>(computedView.getSize().x * skew.x),
                ssvu::toNum<T>(computedView.getSize().y * skew.y));
            if(getMag(offset) != 0)
                computedView.setCenter(
                    view.getCenter() -
                    getVecFromDeg(
                        view.getRotation() + getDeg(offset), getMag(offset)));
            computedView.setCenter(ssvu::toNum<T>(computedView.getCenter().x),
                ssvu::toNum<T>(computedView.getCenter().y));
            mustRecompute = false;
        }

        mRenderTarget.setView(computedView);
    }

    void unapply(sf::RenderTarget& mRenderTarget)
    {
        mRenderTarget.setView(mRenderTarget.getDefaultView());
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
    void update(ssvu::FT mFT)
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
