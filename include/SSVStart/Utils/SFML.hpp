// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_SFML
#define SSVS_UTILS_SFML

#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	namespace Impl
	{
		template<typename T> inline float getLeft(const T& mX) noexcept			{ return mX.left; }
		template<typename T> inline float getTop(const T& mX) noexcept			{ return mX.top; }
		template<typename T> inline float getWidth(const T& mX) noexcept		{ return mX.width; }
		template<typename T> inline float getHeight(const T& mX) noexcept		{ return mX.height; }

		template<typename T> inline float getRight(const T& mX) noexcept		{ return getLeft(mX) + getWidth(mX); }
		template<typename T> inline float getBottom(const T& mX) noexcept		{ return getTop(mX) + getHeight(mX); }
		template<typename T> inline float getHalfWidth(const T& mX) noexcept	{ return getWidth(mX) / 2.f; }
		template<typename T> inline float getHalfHeight(const T& mX) noexcept	{ return getHeight(mX) / 2.f; }

		template<typename T> inline float getCenterX(const T& mX) noexcept		{ return getLeft(mX) + getHalfWidth(mX); }
		template<typename T> inline float getCenterY(const T& mX) noexcept		{ return getTop(mX) + getHalfHeight(mX); }

		template<typename T> inline Vec2f getSize(const T& mX) noexcept			{ return {getWidth(mX), getHeight(mX)}; }
		template<typename T> inline Vec2f getHalfSize(const T& mX) noexcept		{ return {getHalfWidth(mX), getHalfHeight(mX)}; }

		template<typename T> inline Vec2f getNW(const T& mX) noexcept			{ return {getLeft(mX), getTop(mX)}; }
		template<typename T> inline Vec2f getNE(const T& mX) noexcept			{ return {getRight(mX), getTop(mX)}; }
		template<typename T> inline Vec2f getSW(const T& mX) noexcept			{ return {getLeft(mX), getBottom(mX)}; }
		template<typename T> inline Vec2f getSE(const T& mX) noexcept			{ return {getRight(mX), getBottom(mX)}; }

		template<typename T> inline Vec2f getCenter(const T& mX) noexcept		{ return getNW(mX) + getHalfSize(mX); }

		template<typename T> inline Vec2f getCenterN(const T& mX) noexcept		{ return {getCenterX(mX), getTop(mX)}; }
		template<typename T> inline Vec2f getCenterE(const T& mX) noexcept		{ return {getRight(mX), getCenterY(mX)}; }
		template<typename T> inline Vec2f getCenterS(const T& mX) noexcept		{ return {getCenterX(mX), getBottom(mX)}; }
		template<typename T> inline Vec2f getCenterW(const T& mX) noexcept		{ return {getLeft(mX), getCenterY(mX)}; }
	}

	/// @brief Returns global left position of a drawable element.
	template<typename T> inline float getGlobalLeft(const T& mX) noexcept		{ return Impl::getLeft(mX.getGlobalBounds()); }

	/// @brief Returns global top position of a drawable element.
	template<typename T> inline float getGlobalTop(const T& mX) noexcept		{ return Impl::getTop(mX.getGlobalBounds()); }

	/// @brief Returns global width of a drawable element.
	template<typename T> inline float getGlobalWidth(const T& mX) noexcept		{ return Impl::getWidth(mX.getGlobalBounds()); }

	/// @brief Returns global height of a drawable element.
	template<typename T> inline float getGlobalHeight(const T& mX) noexcept		{ return Impl::getHeight(mX.getGlobalBounds()); }

	/// @brief Returns global right position of a drawable element.
	template<typename T> inline float getGlobalRight(const T& mX) noexcept		{ return Impl::getRight(mX.getGlobalBounds()); }

	/// @brief Returns global bottom position of a drawable element.
	template<typename T> inline float getGlobalBottom(const T& mX) noexcept		{ return Impl::getBottom(mX.getGlobalBounds()); }

	/// @brief Returns global half width of a drawable element.
	template<typename T> inline float getGlobalHalfWidth(const T& mX) noexcept	{ return Impl::getHalfWidth(mX.getGlobalBounds()); }

	/// @brief Returns global half height of a drawable element.
	template<typename T> inline float getGlobalHalfHeight(const T& mX) noexcept	{ return Impl::getHalfHeight(mX.getGlobalBounds()); }

	/// @brief Returns global center X of a drawable element.
	template<typename T> inline float getGlobalCenterX(const T& mX) noexcept	{ return Impl::getCenterX(mX.getGlobalBounds()); }

	/// @brief Returns global center X of a drawable element.
	template<typename T> inline float getGlobalCenterY(const T& mX) noexcept	{ return Impl::getCenterY(mX.getGlobalBounds()); }

	/// @brief Returns global size of a drawable element.
	template<typename T> inline Vec2f getGlobalSize(const T& mX) noexcept		{ return Impl::getSize(mX.getGlobalBounds()); }

	/// @brief Returns global halfsize of a drawable element.
	template<typename T> inline Vec2f getGlobalHalfSize(const T& mX) noexcept	{ return Impl::getHalfSize(mX.getGlobalBounds()); }

	/// @brief Returns global NW corner of a drawable element.
	template<typename T> inline Vec2f getGlobalNW(const T& mX) noexcept			{ return Impl::getNW(mX.getGlobalBounds()); }

	/// @brief Returns global NE corner of a drawable element.
	template<typename T> inline Vec2f getGlobalNE(const T& mX) noexcept			{ return Impl::getNE(mX.getGlobalBounds()); }

	/// @brief Returns global SW corner of a drawable element.
	template<typename T> inline Vec2f getGlobalSW(const T& mX) noexcept			{ return Impl::getSW(mX.getGlobalBounds()); }

	/// @brief Returns global SE corner of a drawable element.
	template<typename T> inline Vec2f getGlobalSE(const T& mX) noexcept			{ return Impl::getSE(mX.getGlobalBounds()); }

	/// @brief Returns global center of a drawable element.
	template<typename T> inline Vec2f getGlobalCenter(const T& mX) noexcept		{ return Impl::getCenter(mX.getGlobalBounds()); }

	/// @brief Returns global center-north of a drawable element.
	template<typename T> inline Vec2f getGlobalCenterN(const T& mX) noexcept	{ return Impl::getCenterN(mX.getGlobalBounds()); }

	/// @brief Returns global center-east of a drawable element.
	template<typename T> inline Vec2f getGlobalCenterE(const T& mX) noexcept	{ return Impl::getCenterE(mX.getGlobalBounds()); }

	/// @brief Returns global center-south of a drawable element.
	template<typename T> inline Vec2f getGlobalCenterS(const T& mX) noexcept	{ return Impl::getCenterS(mX.getGlobalBounds()); }

	/// @brief Returns global center-west of a drawable element.
	template<typename T> inline Vec2f getGlobalCenterW(const T& mX) noexcept	{ return Impl::getCenterW(mX.getGlobalBounds()); }



	/// @brief Returns local left position of a drawable element.
	template<typename T> inline float getLocalLeft(const T& mX) noexcept		{ return Impl::getLeft(mX.getLocalBounds()); }

	/// @brief Returns local top position of a drawable element.
	template<typename T> inline float getLocalTop(const T& mX) noexcept			{ return Impl::getTop(mX.getLocalBounds()); }

	/// @brief Returns local width of a drawable element.
	template<typename T> inline float getLocalWidth(const T& mX) noexcept		{ return Impl::getWidth(mX.getLocalBounds()); }

	/// @brief Returns local height of a drawable element.
	template<typename T> inline float getLocalHeight(const T& mX) noexcept		{ return Impl::getHeight(mX.getLocalBounds()); }

	/// @brief Returns local right position of a drawable element.
	template<typename T> inline float getLocalRight(const T& mX) noexcept		{ return Impl::getRight(mX.getLocalBounds()); }

	/// @brief Returns local bottom position of a drawable element.
	template<typename T> inline float getLocalBottom(const T& mX) noexcept		{ return Impl::getBottom(mX.getLocalBounds()); }

	/// @brief Returns local half width of a drawable element.
	template<typename T> inline float getLocalHalfWidth(const T& mX) noexcept	{ return Impl::getHalfWidth(mX.getLocalBounds()); }

	/// @brief Returns local half height of a drawable element.
	template<typename T> inline float getLocalHalfHeight(const T& mX) noexcept	{ return Impl::getHalfHeight(mX.getLocalBounds()); }

	/// @brief Returns local center X of a drawable element.
	template<typename T> inline float getLocalCenterX(const T& mX) noexcept		{ return Impl::getCenterX(mX.getLocalBounds()); }

	/// @brief Returns local center X of a drawable element.
	template<typename T> inline float getLocalCenterY(const T& mX) noexcept		{ return Impl::getCenterY(mX.getLocalBounds()); }

	/// @brief Returns local size of a drawable element.
	template<typename T> inline Vec2f getLocalSize(const T& mX) noexcept		{ return Impl::getSize(mX.getLocalBounds()); }

	/// @brief Returns local halfsize of a drawable element.
	template<typename T> inline Vec2f getLocalHalfSize(const T& mX) noexcept	{ return Impl::getHalfSize(mX.getLocalBounds()); }

	/// @brief Returns local NW corner of a drawable element.
	template<typename T> inline Vec2f getLocalNW(const T& mX) noexcept			{ return Impl::getNW(mX.getLocalBounds()); }

	/// @brief Returns local NE corner of a drawable element.
	template<typename T> inline Vec2f getLocalNE(const T& mX) noexcept			{ return Impl::getNE(mX.getLocalBounds()); }

	/// @brief Returns local SW corner of a drawable element.
	template<typename T> inline Vec2f getLocalSW(const T& mX) noexcept			{ return Impl::getSW(mX.getLocalBounds()); }

	/// @brief Returns local SE corner of a drawable element.
	template<typename T> inline Vec2f getLocalSE(const T& mX) noexcept			{ return Impl::getSE(mX.getLocalBounds()); }

	/// @brief Returns local center of a drawable element.
	template<typename T> inline Vec2f getLocalCenter(const T& mX) noexcept		{ return Impl::getCenter(mX.getLocalBounds()); }

	/// @brief Returns local center-north of a drawable element.
	template<typename T> inline Vec2f getLocalCenterN(const T& mX) noexcept		{ return Impl::getCenterN(mX.getLocalBounds()); }

	/// @brief Returns local center-east of a drawable element.
	template<typename T> inline Vec2f getLocalCenterE(const T& mX) noexcept		{ return Impl::getCenterE(mX.getLocalBounds()); }

	/// @brief Returns local center-south of a drawable element.
	template<typename T> inline Vec2f getLocalCenterS(const T& mX) noexcept		{ return Impl::getCenterS(mX.getLocalBounds()); }

	/// @brief Returns local center-west of a drawable element.
	template<typename T> inline Vec2f getLocalCenterW(const T& mX) noexcept		{ return Impl::getCenterW(mX.getLocalBounds()); }

	/// @brief Sets the origin of a drawable element using a function that returns a `Vec2f`.
	template<typename T> inline void setOrigin(T& mX, Vec2f(*mFn)(const T&)) noexcept { mX.setOrigin(mFn(mX)); }

	/// @brief Creates and returns an sf::Color from HSV values.
	/// @param mH Hue. [0..1]
	/// @param mS Saturation. [0..1]
	/// @param mV Value. [0..1]
	inline auto getColorFromHSV(float mH, float mS, float mV) noexcept
	{
		SSVU_ASSERT(mH >= 0.f && mH <= 1.f);
		SSVU_ASSERT(mS >= 0.f && mS <= 1.f);
		SSVU_ASSERT(mV >= 0.f && mV <= 1.f);

		if(mV == 0.f) return sf::Color::Black;

		float r, g, b;
		auto i((int)std::floor(mH * 6.f));
		auto f((mH * 6) - i);
		auto p(mV * (1.f - mS));
		auto q(mV * (1.f - (mS * f)));
		auto t(mV * (1.f - (mS * (1.f - f))));

		switch(i)
		{
			case 0:				r = mV; g = t; b = p; break;
			case 1:				r = q; g = mV; b = p; break;
			case 2:				r = p; g = mV; b = t; break;
			case 3:				r = p; g = q; b = mV; break;
			case 4:				r = t; g = p; b = mV; break;
			case 5: default:	r = mV; g = p; b = q; break;
		}

		return sf::Color(r * 255.f, g * 255.f, b * 255.f);
	}

	/// @brief Creates and returns an sf::Color from HSV values.
	/// @return Returns an `std::tuple` of [0..1] HSV values.
	inline auto getHSVFromColor(const sf::Color& mX)
	{
		// Credits: lolengine.net/blog/2013/01/13/fast-rgb-to-hsv

		auto r(mX.r / 255.f);
		auto g(mX.g / 255.f);
		auto b(mX.b / 255.f);

		SSVU_ASSERT(r >= 0.f && r <= 1.f);
		SSVU_ASSERT(g >= 0.f && g <= 1.f);
		SSVU_ASSERT(b >= 0.f && b <= 1.f);

		float k{0.f};

		if(g < b)
		{
			std::swap(g, b);
			k = -1.f;
		}

		if(r < g)
		{
			std::swap(r, g);
			k = -2.f / 6.f - k;
		}

		auto chroma(r - std::min(g, b));
		auto h(std::fabs(k + (g - b) / (6.f * chroma + 1e-20f)));
		auto s(chroma / (r + 1e-20f));

		return std::make_tuple(h, s, r);
	}


	/// @brief Creates and returns an sf::Color from an hexadecimal value.
	inline auto getColorFromHex(unsigned int mHex) noexcept
	{
		float r(((mHex >> 16) & 255)), g(((mHex >> 8) & 255)), b(((mHex >> 0) & 255));
		return sf::Color(r, g, b);
	}
}

#endif
