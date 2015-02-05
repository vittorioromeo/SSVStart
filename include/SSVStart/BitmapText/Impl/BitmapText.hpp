// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPTEXT
#define SSVS_BITMAPTEXT_IMPL_BITMAPTEXT

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextDrawState.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextBase.hpp"

namespace ssvs
{
	class BitmapText : public Impl::BitmapTextBase<BitmapText>
	{
		template<typename> friend class Impl::BitmapTextBase;

		public:
			using BaseType = Impl::BitmapTextBase<BitmapText>;

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
				mustRefreshGeometry = false;

				refreshStart();
				createVertices(str);
				refreshFinish();

			}
			inline void refreshColor() const
			{
				if(!mustRefreshColor) return;
				mustRefreshColor = false;

				for(auto& v : vertices) v.color = bdd.colorFG;
			}

		public:
			inline BitmapText() { }
			inline BitmapText(const BitmapFont& mBF, const std::string& mStr = "") : BaseType{mBF}, str{mStr} { }

			template<typename T> inline void setString(T&& mStr) { str = FWD(mStr); mustRefreshGeometry = true; }

			inline void setColor(const sf::Color& mX) noexcept	{ bdd.colorFG = mX; mustRefreshColor = true; }
			inline void setTracking(float mX) noexcept			{ bdd.tracking = mX; mustRefreshGeometry = true; }

			inline const auto& getString() const noexcept { return str; }

			inline void setAlign(TextAlign mX) noexcept { BaseType::setAlign(mX); mustRefreshGeometry = true; }
	};
}

#endif
