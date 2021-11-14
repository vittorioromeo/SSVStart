// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTRECOLORFG
#define SSVS_BITMAPTEXT_BTR_IMPL_BTRECOLORFG

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREWave.hpp"

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include <SSVUtils/Core/Utils/Math.hpp>
#include <SSVUtils/Core/Common/Casts.hpp>
#include <SSVUtils/Core/Common/Frametime.hpp>


namespace ssvs
{
namespace BTR
{
namespace Impl
{
class BTREColor : public BTREffect
{
public:
    enum class Anim
    {
        None,
        Pulse
    };

private:
    sf::Color colorFG, colorFGComputed;
    float pulse{0.f}, pulseSpeed, pulseMax;
    Anim anim{Anim::None};

public:
    inline BTREColor(const sf::Color& mColorFG) noexcept
        : colorFG{mColorFG}, colorFGComputed{colorFG}
    {
    }

    inline void update(ssvu::FT mFT) noexcept override
    {
        if(anim == Anim::Pulse)
        {
            pulse = ssvu::getWrapRad(pulse + (mFT * pulseSpeed));
            colorFGComputed = colorFG;
            colorFGComputed.a =
                ssvu::toInt(255.f - std::abs((std::sin(pulse) * pulseMax)));
        }
    }
    inline void apply(BTRChunk& mX) noexcept override
    {
        mX.forVertices([this](auto, auto, auto& mV, auto&)
            { mV.color = colorFGComputed; });
    }

    inline void setAnimNone() noexcept
    {
        anim = Anim::None;
    }
    inline void setAnimPulse(
        float mSpeed, float mMax, float mStart = 0.f) noexcept
    {
        anim = Anim::Pulse;
        pulse = mStart;
        pulseSpeed = mSpeed;
        pulseMax = mMax;
    }

    inline void setColorFG(const sf::Color& mX) noexcept
    {
        colorFG = mX;
    }
};
} // namespace Impl
} // namespace BTR
} // namespace ssvs

#endif
