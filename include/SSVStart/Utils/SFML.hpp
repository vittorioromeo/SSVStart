// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_SFML
#define SSVS_UTILS_SFML

#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	/// @brief Returns global left position of a drawable element.
	template<typename T> inline float getGlobalLeft(const T& mElement) noexcept		{ return mElement.getGlobalBounds().left; }

	/// @brief Returns global right position of a drawable element.
	template<typename T> inline float getGlobalRight(const T& mElement) noexcept	{ return mElement.getGlobalBounds().left + mElement.getGlobalBounds().width; }

	/// @brief Returns global top position of a drawable element.
	template<typename T> inline float getGlobalTop(const T& mElement) noexcept		{ return mElement.getGlobalBounds().top; }

	/// @brief Returns global bottom position of a drawable element.
	template<typename T> inline float getGlobalBottom(const T& mElement) noexcept	{ return mElement.getGlobalBounds().top + mElement.getGlobalBounds().height; }

	/// @brief Returns global width of a drawable element.
	template<typename T> inline float getGlobalWidth(const T& mElement) noexcept	{ return mElement.getGlobalBounds().width; }

	/// @brief Returns global height of a drawable element.
	template<typename T> inline float getGlobalHeight(const T& mElement) noexcept	{ return mElement.getGlobalBounds().height; }

	/// @brief Returns global size of a drawable element.
	template<typename T> inline Vec2f getGlobalSize(const T& mElement) noexcept		{ return {getGlobalWidth(mElement), getGlobalHeight(mElement)}; }

	/// @brief Returns global halfsize of a drawable element.
	template<typename T> inline Vec2f getGlobalHalfSize(const T& mElement) noexcept	{ return getGlobalSize(mElement) / 2.f; }

	/// @brief Returns global center of a drawable element.
	template<typename T> inline Vec2f getGlobalCenter(const T& mElement) noexcept	{ return Vec2f{getGlobalLeft(mElement), getGlobalTop(mElement)} + getGlobalHalfSize(mElement); }

	/// @brief Returns local left position of a drawable element.
	template<typename T> inline float getLocalLeft(const T& mElement) noexcept		{ return mElement.getLocalBounds().left; }

	/// @brief Returns local right position of a drawable element.
	template<typename T> inline float getLocalRight(const T& mElement) noexcept		{ return mElement.getLocalBounds().left + mElement.getLocalBounds().width; }

	/// @brief Returns local top position of a drawable element.
	template<typename T> inline float getLocalTop(const T& mElement) noexcept		{ return mElement.getLocalBounds().top; }

	/// @brief Returns local bottom position of a drawable element.
	template<typename T> inline float getLocalBottom(const T& mElement) noexcept	{ return mElement.getLocalBounds().top + mElement.getLocalBounds().height; }

	/// @brief Returns local width of a drawable element.
	template<typename T> inline float getLocalWidth(const T& mElement) noexcept		{ return mElement.getLocalBounds().width; }

	/// @brief Returns local height of a drawable element.
	template<typename T> inline float getLocalHeight(const T& mElement) noexcept	{ return mElement.getLocalBounds().height; }

	/// @brief Returns local size of a drawable element.
	template<typename T> inline Vec2f getLocalSize(const T& mElement) noexcept		{ return {getLocalWidth(mElement), getLocalHeight(mElement)}; }

	/// @brief Returns local halfsize of a drawable element.
	template<typename T> inline Vec2f getLocalHalfSize(const T& mElement) noexcept	{ return getLocalSize(mElement) / 2.f; }

	/// @brief Returns local center of a drawable element.
	template<typename T> inline Vec2f getLocalCenter(const T& mElement) noexcept	{ return Vec2f{getLocalLeft(mElement), getLocalTop(mElement)} + getLocalHalfSize(mElement); }

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

	/// @brief Creates and returns an sf::Color from an hexadecimal value.
	inline auto getColorFromHex(unsigned int mHex) noexcept
	{
		float r(((mHex >> 16) & 255)), g(((mHex >> 8) & 255)), b(((mHex >> 0) & 255));
		return sf::Color(r, g, b);
	}
}

#endif
