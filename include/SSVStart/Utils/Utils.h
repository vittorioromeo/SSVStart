// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS
#define SSVS_UTILS

#include <cassert>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SSVUtils/Utils/UtilsMath.h>
#include "SSVStart/Global/Typedefs.h"
#include "SSVStart/GameSystem/GameState.h"

namespace ssvs
{
	class GameState;
	namespace Input { class Trigger; }

	template<typename... TArgs> using CT = ssvu::Common<TArgs...>;

	// Angles
	template<typename T1, typename T2> inline CT<T1, T2> getRadTowards(const Vec2<T1>& mVec, const Vec2<T2>& mTarget) noexcept { return ssvu::getRadTowards(mVec.x, mVec.y, mTarget.x, mTarget.y); }
	template<typename T1, typename T2> inline CT<T1, T2> getDegTowards(const Vec2<T1>& mVec, const Vec2<T2>& mTarget) noexcept { return ssvu::getDegTowards(mVec.x, mVec.y, mTarget.x, mTarget.y); }

	// Collision
	template<typename T> inline bool isPointInPolygon(const std::vector<Vec2<T>>& mVertices, const Vec2<T>& mPoint)
	{
		bool result{false};
		for(std::size_t i{0}, j{mVertices.size() - 1}; i < mVertices.size(); j = i++)
		{
			const auto& vI(mVertices[i]);
			const auto& vJ(mVertices[j]);
			if(((vI.y > mPoint.y) != (vJ.y > mPoint.y)) && (mPoint.x < (vJ.x - vI.x) * (mPoint.y - vI.y) / (vJ.y - vI.y) + vI.x)) result = !result;
		}

		return result;
	}

	// Vec utils
	static Vec2i zeroVec2i{0, 0}; // C++14: template value
	static Vec2f zeroVec2f{0.f, 0.f};

	template<typename T> inline void abs(Vec2<T>& mVec) noexcept { mVec.x = std::abs(mVec.x); mVec.y = std::abs(mVec.y); }
	template<typename T> inline Vec2<T> getAbs(Vec2<T> mVec) noexcept { abs(mVec); return mVec; }
	template<typename T> inline T getMagnitude(const Vec2<T>& mVec) noexcept { return std::sqrt(mVec.x * mVec.x + mVec.y * mVec.y); }
	template<typename T1, typename T2, typename T3> inline void rotateRadAroundCenter(Vec2<T1>& mVec, const Vec2<T2>& mCenter, const T3& mRad)
	{
		CT<T1, T2, T3> s(std::sin(mRad)), c(std::cos(mRad)); mVec -= mCenter;
		mVec = Vec2<CT<T1, T2, T3>>(mVec.x * c - mVec.y * s, mVec.x * s + mVec.y * c) + mCenter;
	}
	template<typename T1, typename T2, typename T3> inline void rotateDegAroundCenter(Vec2<T1>& mVec, const Vec2<T2>& mCenter, const T3& mDeg) { return rotateRadAroundCenter(mVec, mCenter, ssvu::toRad(mDeg)); }
	template<typename T> inline void nullify(Vec2<T>& mVec) noexcept { mVec.x = mVec.y = 0; }
	template<typename T> inline void normalize(Vec2<T>& mVec) noexcept { auto m(getMagnitude(mVec)); if(m != 0) mVec /= m; }
	template<typename T> inline Vec2<T> getNormalized(Vec2<T> mVec) noexcept { normalize(mVec); return mVec; }

	// Resize a vec maintaining direction
	template<typename T1, typename T2> inline void resize(Vec2<T1>& mVec, const T2& mMag) noexcept { normalize(mVec); mVec *= CT<T1, T2>(mMag); }
	template<typename T1, typename T2, typename T3> inline void resize(Vec2<T1>& mVec, const T2& mDesiredMag, const T3& mCurrentMag) noexcept { if(mCurrentMag != 0) mVec /= mCurrentMag; mVec *= mDesiredMag; }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getResized(Vec2<T1> mVec, const T2& mMag) noexcept { resize(mVec, mMag); return mVec; }

	// Component-based vec clamping
	template<typename T1, typename T2, typename T3> inline void cClamp(Vec2<T1>& mVec, const T2& mMin, const T3& mMax) noexcept						{ ssvu::clamp(mVec.x, mMin, mMax); ssvu::clamp(mVec.y, mMin, mMax); }
	template<typename T1, typename T2> inline void cClampMin(Vec2<T1>& mVec, const T2& mMin) noexcept												{ ssvu::clampMin(mVec.x, mMin); ssvu::clampMin(mVec.y, mMin); }
	template<typename T1, typename T2> inline void cClampMax(Vec2<T1>& mVec, const T2& mMax) noexcept												{ ssvu::clampMax(mVec.x, mMax); ssvu::clampMax(mVec.y, mMax); }
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getCClamped(Vec2<T1> mVec, const T2& mMin, const T3& mMax) noexcept	{ cClamp(mVec, mMin, mMax); return mVec; }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getCClampedMin(Vec2<T1> mVec, const T2& mMin) noexcept								{ cClampMin(mVec, mMin); return mVec; }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getCClampedMax(Vec2<T1> mVec, const T2& mMax) noexcept								{ cClampMax(mVec, mMax); return mVec; }

	// Magnitude-based vec clamping
	template<typename T1, typename T2, typename T3> inline void mClamp(Vec2<T1>& mVec, const T2& mMin, const T3& mMax) noexcept
	{
		assert(mMin < mMax);
		const auto& m(getMagnitude(mVec));
		if(m < mMin) resize(mVec, mMin, m);
		else if(m > mMax) resize(mVec, mMax, m);
	}
	template<typename T1, typename T2> inline void mClampMin(Vec2<T1>& mVec, const T2& mMin) noexcept { const auto& m(getMagnitude(mVec)); if(m < mMin) resize(mVec, mMin, m); }
	template<typename T1, typename T2> inline void mClampMax(Vec2<T1>& mVec, const T2& mMax) noexcept { const auto& m(getMagnitude(mVec)); if(m > mMax) resize(mVec, mMax, m); }
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getMClamped(Vec2<T1> mVec, const T2& mMin, const T3& mMax) noexcept	{ mClamp(mVec, mMin, mMax); return mVec; }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getMClampedMin(Vec2<T1> mVec, const T2& mMin) noexcept								{ mClampMin(mVec, mMin); return mVec; }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getMClampedMax(Vec2<T1> mVec, const T2& mMax) noexcept								{ mClampMax(mVec, mMax); return mVec; }

	// Get angle from vec direction
	template<typename T> inline T getRad(Vec2<T> mVec) noexcept			{ normalize(mVec); return std::atan2(mVec.y, mVec.x); }
	template<typename T> inline T getDeg(const Vec2<T>& mVec) noexcept	{ return ssvu::toDeg(getRad(mVec)); }

	// Get unit vec from angle
	template<typename T1, typename T2 = float> inline Vec2<CT<T1, T2>> getVecFromRad(T1 mRad, const T2& mMagnitude = 1.f) { return Vec2<CT<T1, T2>>(mMagnitude * std::cos(mRad), mMagnitude * std::sin(mRad)); }
	template<typename T1, typename T2 = float> inline Vec2<CT<T1, T2>> getVecFromDeg(T1 mDeg, const T2& mMagnitude = 1.f) { return getVecFromRad(ssvu::toRad(mDeg), mMagnitude); }

	// Get direction between two vecs
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getDirection(const Vec2<T1>& mVec, const Vec2<T2>& mTarget) noexcept { return getNormalized(mTarget - mVec); }

	// TODO: document
	template<typename T1, typename T2> inline void truncate(Vec2<T1>& mVec, const T2& mMax) noexcept { auto i(mMax / getMagnitude(mVec)); i = i < 1.f ? i : 1.f; resize(mVec, i); }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getTruncated(Vec2<T1> mVec, const T2& mMax) noexcept { truncate(mVec, mMax); return mVec; }
	template<typename T1, typename T2, typename T3> inline void moveTowards(Vec2<T1>& mVec, const Vec2<T2>& mTarget, const T3& mMagnitude) noexcept { mVec += getDirection(mVec, mTarget) * mMagnitude; }
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getOrbitFromRad(const Vec2<T1>& mVec, const T2& mRad, const T3& mRadius)	{ return mVec + Vec2<CT<T1, T2, T3>>(std::cos(mRad), std::sin(mRad)) * mRadius; }
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getOrbitFromDeg(const Vec2<T1>& mVec, const T2& mDeg, const T3& mRadius)	{ return getOrbitFromRad(mVec, ssvu::toRad(mDeg), mRadius); }
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getMovedTowards(Vec2<T1> mVec, const Vec2<T2>& mTarget, const T3& mMagnitude) noexcept { moveTowards(mVec, mTarget, mMagnitude); return mVec; }
	template<typename T1, typename T2> inline CT<T1, T2> getDotProduct(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return mA.x * mB.x + mA.y * mB.y; }
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getRotatedAroundCenterRad(Vec2<T1> mPoint, const Vec2<T2>& mCenter, const T3& mRad) { rotateRadAroundCenter(mPoint, mCenter, mRad); return mPoint; }
	template<typename T1, typename T2> inline CT<T1, T2> getDistSquaredEuclidean(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept	{ return ssvu::getDistSquaredEuclidean(mA.x, mA.y, mB.x, mB.y); }
	template<typename T1, typename T2> inline CT<T1, T2> getDistEuclidean(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept			{ return ssvu::getDistEuclidean(mA.x, mA.y, mB.x, mB.y); }

	inline void add2StateInput(GameState& mGameState, const Input::Trigger& mTrigger, bool& mValue, Input::Type mType = Input::Type::Always)
	{
		mGameState.addInput(mTrigger, [&mValue](float){ mValue = true; }, [&mValue](float){ mValue = false; }, mType);
	}
	inline void add3StateInput(GameState& mGameState, const Input::Trigger& mNegative, const Input::Trigger& mPositive, int& mValue, Input::Type mType = Input::Type::Always)
	{
		mGameState.addInput(mNegative, [&mValue](float){ mValue = -1; },	[&mValue](float){ if(mValue == -1) mValue = 0; }, mType);
		mGameState.addInput(mPositive, [&mValue](float){ mValue = 1; },		[&mValue](float){ if(mValue == 1) mValue = 0; }, mType);
	}

	// SFML element utils
	template<typename T> float getGlobalLeft(const T& mElement)	noexcept	{ return mElement.getGlobalBounds().left; }
	template<typename T> float getGlobalRight(const T& mElement) noexcept	{ return mElement.getGlobalBounds().left + mElement.getGlobalBounds().width; }
	template<typename T> float getGlobalTop(const T& mElement) noexcept		{ return mElement.getGlobalBounds().top; }
	template<typename T> float getGlobalBottom(const T& mElement) noexcept	{ return mElement.getGlobalBounds().top + mElement.getGlobalBounds().height; }
	template<typename T> float getGlobalWidth(const T& mElement) noexcept	{ return mElement.getGlobalBounds().width; }
	template<typename T> float getGlobalHeight(const T& mElement) noexcept	{ return mElement.getGlobalBounds().height; }

	template<typename T> float getLocalLeft(const T& mElement) noexcept		{ return mElement.getLocalBounds().left; }
	template<typename T> float getLocalRight(const T& mElement) noexcept	{ return mElement.getLocalBounds().left + mElement.getLocalBounds().width; }
	template<typename T> float getLocalTop(const T& mElement) noexcept		{ return mElement.getLocalBounds().top; }
	template<typename T> float getLocalBottom(const T& mElement) noexcept	{ return mElement.getLocalBounds().top + mElement.getLocalBounds().height; }
	template<typename T> float getLocalWidth(const T& mElement) noexcept	{ return mElement.getLocalBounds().width; }
	template<typename T> float getLocalHeight(const T& mElement) noexcept	{ return mElement.getLocalBounds().height; }

	// AABB utils
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getCenter(const Vec2<T1>& mMin, const Vec2<T2>& mMax) noexcept	{ return Vec2<CT<T1, T2>>(mMin.x + (mMax.x - mMin.x) / CT<T1, T2>(2), mMin.y + (mMax.y - mMin.y) / CT<T1, T2>(2)); }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getHalfSize(const Vec2<T1>& mMin, const Vec2<T2>& mMax) noexcept	{ return Vec2<CT<T1, T2>>((mMax.x - mMin.x) / CT<T1, T2>(2), (mMax.y - mMin.y) / CT<T1, T2>(2)); }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getSize(const Vec2<T1>& mMin, const Vec2<T2>& mMax) noexcept		{ return getHalfSize(mMin, mMax) * CT<T1, T2>(2); }
}

#endif
