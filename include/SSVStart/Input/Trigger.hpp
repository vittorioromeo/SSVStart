// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_TRIGGER
#define SSVS_INPUT_TRIGGER

#include "SSVStart/Input/Combo.hpp"

#include <SSVUtils/Core/Utils/Macros.hpp>

namespace ssvs
{
    namespace Input
    {
        class Trigger
        {
        private:
            std::vector<Combo> combos;

        public:
            inline Trigger() = default;
            inline Trigger(const std::initializer_list<Combo>& mCombos) noexcept
                : combos{mCombos}
            {
            }

            inline bool SSVU_ATTRIBUTE(pure) operator==(
                const Trigger& mRhs) const noexcept
            {
                return combos == mRhs.combos;
            }

            inline bool SSVU_ATTRIBUTE(pure) operator!=(
                const Trigger& mRhs) const noexcept
            {
                return !this->operator==(mRhs);
            }

            inline auto& getCombos() noexcept { return combos; }
            inline const auto& getCombos() const noexcept { return combos; }
        };
    }
}

#endif
