// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPTEXT
#define SSVS_BITMAPTEXT_IMPL_BITMAPTEXT

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextData.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextBase.hpp"

namespace ssvs
{
	class BitmapText : public Impl::BitmapTextBase<BitmapText>
	{
		template<typename> friend class Impl::BitmapTextBase;

		private:
			std::string str;
			mutable bool mustRefreshGeometry{true}, mustRefreshColor{true};

			inline void refresh() const
			{
				refreshGeometry();
				refreshColor();
			}
			inline void refreshGeometry() const
			{
				if(!mustRefreshGeometry) return;
				SSVU_ASSERT(bitmapFont != nullptr);

				bdd.reset(*bitmapFont);

				vertices.clear();
				createVertices(str);

				mustRefreshGeometry = false;
			}
			inline void refreshColor() const
			{
				if(!mustRefreshColor) return;
				for(auto& v : vertices) v.color = bdd.colorFG;
				mustRefreshColor = false;
			}

		public:
			// inline BitmapText() : Impl::BitmapTextBase<BitmapText>{}  { }
			inline BitmapText(const BitmapFont& mBitmapFont, std::string mStr = "") : Impl::BitmapTextBase<BitmapText>{mBitmapFont}, str{mStr} { }

			template<typename T> inline void setString(T&& mStr) { str = ssvu::fwd<T>(mStr); mustRefreshGeometry = true; }

			inline void setColor(const sf::Color& mColor) noexcept { bdd.colorFG = mColor; mustRefreshColor = true; }
			inline void setTracking(float mTracking) noexcept { bdd.tracking = mTracking; mustRefreshGeometry = true; }

			inline const auto& getString() const noexcept { return str; }
	};
}

#endif
