// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_SFML
#define SSVS_UTILS_SFML

#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	/// @brief Returns global left position of a drawable element.
	template<typename T> inline float getGlobalLeft(const T& mElement)	noexcept	{ return mElement.getGlobalBounds().left; }

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
}

#endif
