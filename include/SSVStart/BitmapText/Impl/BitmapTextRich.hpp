// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPTEXTRICH
#define SSVS_BITMAPTEXT_IMPL_BITMAPTEXTRICH

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextDrawState.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextBase.hpp"
#include "SSVStart/BitmapText/Impl/Parts.hpp"

namespace ssvs
{
	class BitmapTextRich : public Impl::BitmapTextBase<BitmapTextRich>
	{
		template<typename> friend class Impl::BitmapTextBase;

		friend class BTRPart;
		friend class BTRPString;
		friend class BTRPColorFG;
		friend class BTRPTracking;

		public:
			using BaseType = Impl::BitmapTextBase<BitmapTextRich>;

		private:
			PartRecycler partRecycler;
			std::vector<PartPtr> partManager;
			BTRPart* basePart{&createPart<BTRPart>()};
			mutable bool mustRefresh{true};

			inline void refresh() const
			{
				if(!mustRefresh) return;
				mustRefresh = false;

				refreshStart();

				bdd.tracking = 0.f;
				bdd.colorFG = sf::Color::White;
				basePart->apply();

				refreshFinish();
			}

			inline void applyStr(const std::string& mStr) const { createVertices(mStr); }
			inline void applyColorFG(const sf::Color& mColor) const noexcept { bdd.colorFG = mColor; }
			inline void applyTracking(float mTracking) const noexcept { bdd.tracking = mTracking; }

			template<typename T, typename... TArgs> inline T& createPart(TArgs&&... mArgs)
			{
				return partRecycler.getCreateEmplace<T>(partManager, *this, SSVU_FWD(mArgs)...);
			}

		public:
			inline BitmapTextRich() { }
			inline BitmapTextRich(const BitmapFont& mBF) : BaseType{mBF} { }

			inline void clear()
			{
				// basePart->clear();
				partManager.clear();
			}
			inline void update(FT mFT) { basePart->update(mFT); }

			template<typename T, typename... TArgs> auto& mk(TArgs&&... mArgs);
			template<typename T> auto& operator<<(T&&);

			inline void setAlign(TextAlign mX) noexcept { BaseType::setAlign(mX); mustRefresh = true; }
	};
}

#endif

// TODO: do not refresh geometry when only color is chagned
