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

	using ITrigger = Input::Trigger;
	using IType = Input::Type;
	using IMode = Input::Mode;
	template<typename... TArgs> using CT = ssvu::Common<TArgs...>;

	/// @brief Calculates radians needed to turn towards a point.
	/// @param mVec Starting point.
	/// @param mTarget Target point.
	/// @return Returns the needed radians.
	template<typename T1, typename T2> inline CT<T1, T2> getRadTowards(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return ssvu::getRadTowards(mA.x, mA.y, mB.x, mB.y); }

	/// @brief Calculates degrees needed to turn towards a point.
	/// @param mVec Starting point.
	/// @param mTarget Target point.
	/// @return Returns the needed degrees.
	template<typename T1, typename T2> inline CT<T1, T2> getDegTowards(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return ssvu::getDegTowards(mA.x, mA.y, mB.x, mB.y); }

	/// @brief Checks if a point is inside a polygon.
	/// @param mVertices Container of the polygon vertices.
	/// @param mPoint Point to check.
	/// @return Returns true if the point is inside the polygon.
	template<typename TC, typename T> inline bool isPointInPolygon(const TC& mVertices, const Vec2<T>& mPoint)
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

	/// @brief Static value representing a (0, 0) vector. (int)
	static Vec2i zeroVec2i{0, 0}; // C++14: template value

	/// @brief Static value representing a (0, 0) vector. (float)
	static Vec2f zeroVec2f{0.f, 0.f};

	/// @brief Static value representing a (0, 0) vector. (unsigned int)
	static Vec2u zeroVec2u{0u, 0u};

	/// @brief Sets a vector's components to their absolute values.
	/// @details Calls std::abs on both components.
	/// @param mVec Vector to modify.
	template<typename T> inline void abs(Vec2<T>& mVec) noexcept { mVec.x = std::abs(mVec.x); mVec.y = std::abs(mVec.y); }

	/// @brief Returns a vector whose components are the absolute values of the original's.
	/// @details Uses std::abs on both components.
	/// @param mVec Original vector. (will not be modified)
	///	@return Returns a new vector with absolute value components.
	template<typename T> inline Vec2<T> getAbs(Vec2<T> mVec) noexcept { abs(mVec); return mVec; }

	/// @brief Get the magnitude of a vector, squared.
	/// @param mVec Vector to use.
	///	@return Returns the squared magnitude of mVec.
	template<typename T> inline T getMagSquared(const Vec2<T>& mVec) noexcept { return mVec.x * mVec.x + mVec.y * mVec.y; }

	/// @brief Get the magnitude of a vector.
	/// @param mVec Vector to use.
	///	@return Returns the magnitude of mVec.
	template<typename T> inline T getMag(const Vec2<T>& mVec) noexcept { return std::sqrt(getMagSquared(mVec)); }

	/// @brief Rotates a vector by n radians around a point.
	/// @param mVec Vector to rotate. (will be modified)
	/// @param mCenter Point to use as center for the rotation.
	/// @param mRad Number of radians.
	template<typename T1, typename T2, typename T3> inline void rotateRadAroundCenter(Vec2<T1>& mVec, const Vec2<T2>& mCenter, const T3& mRad)
	{
		auto s(std::sin(mRad)), c(std::cos(mRad)); mVec -= mCenter;
		mVec = Vec2<T1>(mVec.x * c - mVec.y * s, mVec.x * s + mVec.y * c) + mCenter;
	}

	/// @brief Rotates a vector by n degrees around a point.
	/// @param mVec Vector to rotate. (will be modified)
	/// @param mCenter Point to use as center for the rotation.
	/// @param mRad Number of degrees.
	template<typename T1, typename T2, typename T3> inline void rotateDegAroundCenter(Vec2<T1>& mVec, const Vec2<T2>& mCenter, const T3& mDeg)
	{
		return rotateRadAroundCenter(mVec, mCenter, ssvu::toRad(mDeg));
	}

	/// @brief Sets a vector's components to 0.
	/// @param mVec Vector to nullify. (will be modified)
	template<typename T> inline void nullify(Vec2<T>& mVec) noexcept { mVec.x = mVec.y = 0; }

	/// @brief Normalizes a vector. (known magnitude)
	/// @details Internally checks if the magnitude is not 0.
	/// @param mVec Vector to normalize. (will be modified)
	///	@param mMag Vector's current magnitude.
	template<typename T1, typename T2> inline void normalize(Vec2<T1>& mVec, const T2& mMag) noexcept { if(mMag != 0) mVec /= mMag; }

	/// @brief Normalizes a vector.
	/// @details Internally checks if the magnitude is not 0.
	/// @param mVec Vector to normalize. (will be modified)
	template<typename T> inline void normalize(Vec2<T>& mVec) noexcept { normalize(mVec, getMag(mVec)); }

	/// @brief Gets a normalized copy of the original vector. (known magnitude)
	/// @details Internally checks if the magnitude is not 0.
	/// @param mVec Original vector. (will not be modified)
	///	@param mMag Vector's current magnitude.
	/// @return Returns a copy of the original vector, normalized.
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getNormalized(Vec2<T1> mVec, const T2& mMag) noexcept { normalize(mVec, mMag); return mVec; }

	/// @brief Gets a normalized copy of the original vector.
	/// @details Internally checks if the magnitude is not 0.
	/// @param mVec Original vector. (will not be modified)
	/// @return Returns a copy of the original vector, normalized.
	template<typename T> inline Vec2<T> getNormalized(Vec2<T> mVec) noexcept { normalize(mVec); return mVec; }

	/// @brief Resizes a vector. (known magnitude)
	/// @details Internally multiplies by the desired magnitude.
	/// @param mVec Vector to resize. (will be modified)
	/// @param mMag Desired magnitude.
	/// @param mCrntMag Current magnitude.
	template<typename T1, typename T2, typename T3> inline void resize(Vec2<T1>& mVec, const T2& mMag, const T3& mCrntMag) noexcept { normalize(mVec, mCrntMag); mVec *= CT<T1, T2>(mMag); }

	/// @brief Resizes a vector.
	/// @details Internally normalizes the vector and multiplies by the desired magnitude.
	/// @param mVec Vector to resize. (will be modified)
	/// @param mMag Desired magnitude.
	template<typename T1, typename T2> inline void resize(Vec2<T1>& mVec, const T2& mMag) noexcept { resize(mVec, mMag, getMag(mVec)); }

	/// @brief Gets a resized copy of the original vector.
	/// @details Internally normalizes the vector and multiplies by the desired magnitude.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMag Desired magnitude.
	/// @return Returns a copy of the original vector, resized.
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getResized(Vec2<T1> mVec, const T2& mMag) noexcept { resize(mVec, mMag); return mVec; }

	/// @brief Gets a resized copy of the original vector. (known magnitude)
	/// @details Internally normalizes the vector and multiplies by the desired magnitude.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMag Desired magnitude.
	/// @param mCrntMag Current magnitude.
	/// @return Returns a copy of the original vector, resized.
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getResized(Vec2<T1> mVec, const T2& mMag, const T3& mCrntMag) noexcept { resize(mVec, mMag, mCrntMag); return mVec; }

	/// @brief Clamps a vector's components.
	/// @details Internally calls ssvu::clamp on both components.
	/// @param mVec Vector to clamp. (will be modified)
	/// @param mMin Min component value.
	/// @param mMax Max component value.
	template<typename T1, typename T2, typename T3> inline void cClamp(Vec2<T1>& mVec, const T2& mMin, const T3& mMax) noexcept { ssvu::clamp(mVec.x, mMin, mMax); ssvu::clamp(mVec.y, mMin, mMax); }

	/// @brief Clamps a vector's components. (min only)
	/// @details Internally calls ssvu::clampMin on both components.
	/// @param mVec Vector to clamp. (will be modified)
	/// @param mMin Min component value.
	template<typename T1, typename T2> inline void cClampMin(Vec2<T1>& mVec, const T2& mMin) noexcept { ssvu::clampMin(mVec.x, mMin); ssvu::clampMin(mVec.y, mMin); }

	/// @brief Clamps a vector's components. (max only)
	/// @details Internally calls ssvu::clampMax on both components.
	/// @param mVec Vector to clamp. (will be modified)
	/// @param mMax Max component value.
	template<typename T1, typename T2> inline void cClampMax(Vec2<T1>& mVec, const T2& mMax) noexcept { ssvu::clampMax(mVec.x, mMax); ssvu::clampMax(mVec.y, mMax); }

	/// @brief Gets a vector with clamped components.
	/// @details Internally calls ssvu::clamp on the copy's both components.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMin Min component value.
	/// @param mMax Max component value.
	/// @return Returns a copy of the original vector, clamped.
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getCClamped(Vec2<T1> mVec, const T2& mMin, const T3& mMax) noexcept { cClamp(mVec, mMin, mMax); return mVec; }

	/// @brief Gets a vector with clamped components. (min only)
	/// @details Internally calls ssvu::clampMin on the copy's both components.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMin Min component value.
	/// @return Returns a copy of the original vector, clamped.
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getCClampedMin(Vec2<T1> mVec, const T2& mMin) noexcept { cClampMin(mVec, mMin); return mVec; }

	/// @brief Gets a vector with clamped components. (max only)
	/// @details Internally calls ssvu::clampMax on the copy's both components.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMax Max component value.
	/// @return Returns a copy of the original vector, clamped.
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getCClampedMax(Vec2<T1> mVec, const T2& mMax) noexcept { cClampMax(mVec, mMax); return mVec; }

	/// @brief Clamps a vector's magnitude.
	/// @details Internally resizes the vector, if needed.
	/// @param mVec Vector to clamp. (will be modified)
	/// @param mMin Min magnitude.
	/// @param mMax Max magnitude.
	template<typename T1, typename T2, typename T3> inline void mClamp(Vec2<T1>& mVec, const T2& mMin, const T3& mMax) noexcept
	{
		assert(mMin < mMax);
		const auto& m(getMag(mVec));
		if(m < mMin) resize(mVec, mMin, m);
		else if(m > mMax) resize(mVec, mMax, m);
	}

	/// @brief Clamps a vector's magnitude. (min only)
	/// @details Internally resizes the vector, if needed.
	/// @param mVec Vector to clamp. (will be modified)
	/// @param mMin Min magnitude.
	template<typename T1, typename T2> inline void mClampMin(Vec2<T1>& mVec, const T2& mMin) noexcept { const auto& m(getMag(mVec)); if(m < mMin) resize(mVec, mMin, m); }

	/// @brief Clamps a vector's magnitude. (max only)
	/// @details Internally resizes the vector, if needed.
	/// @param mVec Vector to clamp. (will be modified)
	/// @param mMax Max magnitude.
	template<typename T1, typename T2> inline void mClampMax(Vec2<T1>& mVec, const T2& mMax) noexcept { const auto& m(getMag(mVec)); if(m > mMax) resize(mVec, mMax, m); }

	/// @brief Gets a vector with clamped magnitude.
	/// @details Internally resizes a copy of the vector, if needed.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMin Min magnitude.
	/// @param mMax Max magnitude.
	/// @return Returns a copy of the original vector, clamped.
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getMClamped(Vec2<T1> mVec, const T2& mMin, const T3& mMax) noexcept	{ mClamp(mVec, mMin, mMax); return mVec; }

	/// @brief Gets a vector with clamped magnitude. (min only)
	/// @details Internally resizes a copy of the vector, if needed.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMin Min magnitude.
	/// @return Returns a copy of the original vector, clamped.
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getMClampedMin(Vec2<T1> mVec, const T2& mMin) noexcept { mClampMin(mVec, mMin); return mVec; }

	/// @brief Gets a vector with clamped magnitude. (max only)
	/// @details Internally resizes a copy of the vector, if needed.
	/// @param mVec Original vector. (will not be modified)
	/// @param mMin Max magnitude.
	/// @return Returns a copy of the original vector, clamped.
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getMClampedMax(Vec2<T1> mVec, const T2& mMax) noexcept { mClampMax(mVec, mMax); return mVec; }

	/// @brief Gets the angle of a vector in radians.
	/// @param mVec Vector to use. (will not be modified)
	/// @return Returns the angle of mVec.
	template<typename T> inline T getRad(const Vec2<T>& mVec) noexcept { return std::atan2(mVec.y, mVec.x); }

	/// @brief Gets the angle of between two vectors in radians.
	/// @param mA First vector.
	/// @param mB Second vector.
	/// @return Returns the angle between mA and mB.
	template<typename T1, typename T2> inline CT<T1, T2> getRad(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return std::atan2(mB.y - mA.y, mB.x - mA.x); }

	/// @brief Gets the angle of a vector in degrees.
	/// @param mVec Vector to use. (will not be modified)
	/// @return Returns the angle of mVec.
	template<typename T> inline T getDeg(const Vec2<T>& mVec) noexcept { return ssvu::toDeg(getRad(mVec)); }

	/// @brief Gets the angle of between two vectors in degrees.
	/// @param mA First vector.
	/// @param mB Second vector.
	/// @return Returns the angle between mA and mB.
	template<typename T1, typename T2> inline CT<T1, T2> getDeg(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return ssvu::toDeg(getRad(mA, mB)); }

	/// @brief Gets a vector from an angle. (from radians)
	/// @param mRad Radians of the desired vector.
	/// @param mMag Magnitude of the desired vector. (defaults to 1)
	/// @return Returns a new vector with specified angle and magnitude.
	template<typename T1, typename T2 = float> inline Vec2<CT<T1, T2>> getVecFromRad(const T1& mRad, const T2& mMag = 1.f) { return Vec2<CT<T1, T2>>(mMag * std::cos(mRad), mMag * std::sin(mRad)); }

	/// @brief Gets a vector from an angle. (from degrees)
	/// @param mRad Degrees of the desired vector.
	/// @param mMag Magnitude of the desired vector. (defaults to 1)
	/// @return Returns a new vector with specified angle and magnitude.
	template<typename T1, typename T2 = float> inline Vec2<CT<T1, T2>> getVecFromDeg(const T1& mDeg, const T2& mMag = 1.f) { return getVecFromRad(ssvu::toRad(mDeg), mMag); }

	/// @brief Gets the direction vector between two vectors.
	/// @param mA First vector.
	/// @param mB Second vector.
	/// @return Returns mB - mA, normalized
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getDirVec(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return getNormalized(mB - mA); }

	/// @brief Moves a point towards another point.
	/// @param mA First vector. (will be modified)
	/// @param mB Second vector. (target point)
	/// @param mMag Magnitude of the translation.
	template<typename T1, typename T2, typename T3> inline void moveTowards(Vec2<T1>& mA, const Vec2<T2>& mB, const T3& mMag) noexcept { mA += getDirVec(mA, mB) * mMag; }

	/// @brief Gets a point moved towards another point.
	/// @param mA First vector. (will not be modified)
	/// @param mB Second vector. (target point)
	/// @param mMag Magnitude of the translation.
	/// @return Returns a copy of mA moved towards mB.
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getMovedTowards(Vec2<T1> mA, const Vec2<T2>& mB, const T3& mMag) noexcept { moveTowards(mA, mB, mMag); return mA; }

	/// @brief Gets a point orbited around another point.
	/// @param mVec Center of the orbit.
	/// @param mRad Radians of the orbit.
	/// @param mRadius Radius of the orbit.
	/// @return Returns a copy of mVec, orbited by mRad radians and mRadius radius.
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getOrbitRad(const Vec2<T1>& mVec, const T2& mRad, const T3& mRadius) { return Vec2<CT<T1, T2, T3>>(mVec) + getVecFromRad(mRad, mRadius); }

	/// @brief Gets a point orbited around another point.
	/// @param mVec Center of the orbit.
	/// @param mDeg Degrees of the orbit.
	/// @param mRadius Radius of the orbit.
	/// @return Returns a copy of mVec, orbited by mDeg degrees and mRadius radius.
	template<typename T1, typename T2, typename T3> inline Vec2<CT<T1, T2, T3>> getOrbitDeg(const Vec2<T1>& mVec, const T2& mDeg, const T3& mRadius) { return getOrbitRad(mVec, ssvu::toRad(mDeg), mRadius); }

	/// @brief Gets the dot product between two vectors.
	/// @param mA First vector.
	/// @param mB Second vector.
	/// @return Returns the dot product between mA and mB.
	template<typename T1, typename T2> inline CT<T1, T2> getDotProduct(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return mA.x * mB.x + mA.y * mB.y; }

	/// @brief Calculates Euclidean distance (squared) between two points.
	/// @param mA First point.
	/// @param mB Second point.
	/// @return Returns the calculated distance (squared).
	template<typename T1, typename T2> inline CT<T1, T2> getDistSquaredEuclidean(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return ssvu::getDistSquaredEuclidean(mA.x, mA.y, mB.x, mB.y); }

	/// @brief Calculates Euclidean distance between two points.
	/// @param mA First point.
	/// @param mB Second point.
	/// @return Returns the calculated distance.
	template<typename T1, typename T2> inline CT<T1, T2> getDistEuclidean(const Vec2<T1>& mA, const Vec2<T2>& mB) noexcept { return ssvu::getDistEuclidean(mA.x, mA.y, mB.x, mB.y); }

	// TODO: document
	inline void add2StateInput(GameState& mGameState, const ITrigger& mTrigger, bool& mValue, IType mType = IType::Always, IMode mMode = IMode::Overlap)
	{
		mGameState.addInput(mTrigger, [&mValue](float){ mValue = true; }, [&mValue](float){ mValue = false; }, mType, mMode);
	}
	inline void add3StateInput(GameState& mGameState, const ITrigger& mNegative, const ITrigger& mPositive, int& mValue, IType mType = IType::Always, IMode mMode = IMode::Overlap)
	{
		mGameState.addInput(mNegative, [&mValue](float){ mValue = -1; },	[&mValue](float){ if(mValue == -1) mValue = 0; }, mType, mMode);
		mGameState.addInput(mPositive, [&mValue](float){ mValue = 1; },		[&mValue](float){ if(mValue == 1) mValue = 0; }, mType, mMode);
	}

	// SFML element utils
	template<typename T> float getGlobalLeft(const T& mElement)	noexcept		{ return mElement.getGlobalBounds().left; }
	template<typename T> float getGlobalRight(const T& mElement) noexcept		{ return mElement.getGlobalBounds().left + mElement.getGlobalBounds().width; }
	template<typename T> float getGlobalTop(const T& mElement) noexcept			{ return mElement.getGlobalBounds().top; }
	template<typename T> float getGlobalBottom(const T& mElement) noexcept		{ return mElement.getGlobalBounds().top + mElement.getGlobalBounds().height; }
	template<typename T> float getGlobalWidth(const T& mElement) noexcept		{ return mElement.getGlobalBounds().width; }
	template<typename T> float getGlobalHeight(const T& mElement) noexcept		{ return mElement.getGlobalBounds().height; }
	template<typename T> Vec2f getGlobalSize(const T& mElement) noexcept		{ return {getGlobalWidth(mElement), getGlobalHeight(mElement)}; }
	template<typename T> Vec2f getGlobalHalfSize(const T& mElement) noexcept	{ return getGlobalSize(mElement) / 2.f; }

	template<typename T> float getLocalLeft(const T& mElement) noexcept			{ return mElement.getLocalBounds().left; }
	template<typename T> float getLocalRight(const T& mElement) noexcept		{ return mElement.getLocalBounds().left + mElement.getLocalBounds().width; }
	template<typename T> float getLocalTop(const T& mElement) noexcept			{ return mElement.getLocalBounds().top; }
	template<typename T> float getLocalBottom(const T& mElement) noexcept		{ return mElement.getLocalBounds().top + mElement.getLocalBounds().height; }
	template<typename T> float getLocalWidth(const T& mElement) noexcept		{ return mElement.getLocalBounds().width; }
	template<typename T> float getLocalHeight(const T& mElement) noexcept		{ return mElement.getLocalBounds().height; }
	template<typename T> Vec2f getLocalSize(const T& mElement) noexcept			{ return {getLocalWidth(mElement), getLocalHeight(mElement)}; }
	template<typename T> Vec2f getLocalHalfSize(const T& mElement) noexcept		{ return getLocalSize(mElement) / 2.f; }

	// AABB utils
	// TODO: put AABB class here from SSVSC?
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getCenter(const Vec2<T1>& mMin, const Vec2<T2>& mMax) noexcept	{ return Vec2<CT<T1, T2>>(mMin.x + (mMax.x - mMin.x) / CT<T1, T2>(2), mMin.y + (mMax.y - mMin.y) / CT<T1, T2>(2)); }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getHalfSize(const Vec2<T1>& mMin, const Vec2<T2>& mMax) noexcept	{ return Vec2<CT<T1, T2>>((mMax.x - mMin.x) / CT<T1, T2>(2), (mMax.y - mMin.y) / CT<T1, T2>(2)); }
	template<typename T1, typename T2> inline Vec2<CT<T1, T2>> getSize(const Vec2<T1>& mMin, const Vec2<T2>& mMax) noexcept		{ return getHalfSize(mMin, mMax) * CT<T1, T2>(2); }
}

#endif
