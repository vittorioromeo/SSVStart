// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTREWAVE
#define SSVS_BITMAPTEXT_BTR_IMPL_BTREWAVE

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.hpp"

namespace ssvs
{
    namespace BTR
    {
        namespace Impl
        {
            class BTREWave : public BTREffect
            {
            private:
                float angle, amplitude, repeat, speedMult;

            public:
                inline BTREWave(float mAmplitude = 2.f, float mSpeedMult = 0.1f,
                    float mRepeat = 4.f, float mAngleStart = 0.f)
                    : angle{mAngleStart}, amplitude{mAmplitude},
                      repeat{mRepeat}, speedMult{mSpeedMult}
                {
                }

                inline void update(FT mFT) noexcept override
                {
                    angle = ssvu::getWrapRad(angle + mFT * speedMult);
                }
                inline void apply(BTRChunk& mX) noexcept override
                {
                    mX.forVertices([this](auto mIdx, auto, auto& mV, auto& mVO)
                        {
                            mV.position.y =
                                mVO.position.y +
                                std::sin(angle + (mIdx / repeat)) * amplitude;
                        });
                }
            };
        }
    }
}

#endif
