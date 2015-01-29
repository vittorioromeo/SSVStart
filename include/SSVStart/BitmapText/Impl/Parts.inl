// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_PARTS_INL
#define SSVS_BITMAPTEXT_IMPL_PARTS_INL

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/Parts.hpp"
#include "SSVStart/Utils/SFML.hpp"

namespace ssvs
{
	inline void BTRPart::setEnabled(bool mX) noexcept
	{
		if(enabled != mX) btr.mustRefresh = true;
		enabled = mX;

		for(auto c : children) c->setEnabled(mX);
	}

	template<typename T, typename... TArgs> auto& BTRPart::mk(TArgs&&... mArgs)					{ return btr.createPart<T>(ssvu::fwd<TArgs>(mArgs)...); }
	template<typename T, typename... TArgs> auto& BTRPart::mk(T*& mTarget, TArgs&&... mArgs)	{ mTarget = &mk<T>(ssvu::fwd<TArgs>(mArgs)...); return *mTarget; }

	inline auto& BTRPart::operator<<(BTRPart& mX)			{ adopt(mX);							return *this; }
	inline auto& BTRPart::operator<<(const std::string& mX)	{ adopt(mk<BTRP::Str>(mX));				return *this; }
	inline auto& BTRPart::operator<<(std::string&& mX)		{ adopt(mk<BTRP::Str>(std::move(mX)));	return *this; }
	inline auto& BTRPart::operator<<(const sf::Color& mX)	{ adopt(mk<BTRP::ClFG>(mX));			return *this; }



	// BTRPString
	inline void BTRPString::apply()
	{
		btr.applyStr(str);
		BTRPart::apply();
	}
	template<typename T> inline void BTRPString::setStr(T&& mX)
	{
		if(str != mX) btr.mustRefresh = true;
		str = ssvu::fwd<T>(mX);
	}

	// BTRPColorFG
	inline void BTRPColorFG::apply()
	{
		btr.applyColorFG(computed);
		BTRPart::apply();
	}
	inline void BTRPColorFG::setColor(const sf::Color& mX)
	{
		if(color != mX) btr.mustRefresh = true;
		color = mX;
		computed = color;
	}
	inline void BTRPColorFG::update(FT mFT)
	{
		if(anim == Anim::Pulse)
		{
			pulse = ssvu::wrapRad(pulse + (mFT * pulseSpeed));
			computed = color;
			computed.a = static_cast<int>(255.f - std::abs((std::sin(pulse) * pulseMax)));
			btr.mustRefresh = true;
		}

		// auto x = getHSVFromColor(computed);
		// std::get<0>(x) = std::fmod(std::get<0>(x) + (mFT * 0.01f), 1.0f);
		// computed = getColorFromHSV(std::get<0>(x), std::get<1>(x), std::get<2>(x));
		// btr.mustRefresh = true;

		BTRPart::update(mFT);
	}

	// BTRPTracking
	inline void BTRPTracking::apply()
	{
		btr.applyTracking(tracking);
		BTRPart::apply();
	}
	inline void BTRPTracking::setTracking(float mX)
	{
		if(tracking != mX) btr.mustRefresh = true;
		tracking = mX;
	}
}

#endif
