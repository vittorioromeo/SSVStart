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
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Global/Typedefs.h"
#include "SSVStart/GameSystem/GameState.h"

namespace ssvs
{
	class GameState;
	namespace Input { class Trigger; }

	namespace Utils
	{
		// Angles
		template<typename T> inline T getRadiansTowards(const Vec2<T>& mVec, const Vec2<T>& mTarget) { return atan2(mTarget.y - mVec.y, mTarget.x - mVec.x); }
		template<typename T> inline T getDegreesTowards(const Vec2<T>& mVec, const Vec2<T>& mTarget) { return ssvu::toDegrees(getRadiansToPoint(mVec, mTarget)); }

		// Collision
		inline bool isPointInPolygon(const std::vector<Vec2f>& mVertices, Vec2f mPoint)
		{
			bool result{false};
			size_t vCount{mVertices.size()};

			for(size_t i{0}, j{vCount - 1}; i < vCount; j = i++)
			{
				const auto& vI(mVertices[i]);
				const auto& vJ(mVertices[j]);

				if(((vI.y > mPoint.y) != (vJ.y > mPoint.y)) && (mPoint.x < (vJ.x - vI.x) * (mPoint.y - vI.y) / (vJ.y - vI.y) + vI.x))
					result = !result;
			}

			return result;
		}

		// Vec utils
		template<typename T> inline T getMagnitude(const Vec2<T>& mVec) { return sqrt(mVec.x * mVec.x + mVec.y * mVec.y); }
		template<typename T> void rotateAroundCenter(Vec2<T>& mVec, const Vec2<T>& mCenter, float mRadians)
		{
			float s(sin(mRadians)), c(cos(mRadians)); mVec -= mCenter;
			Vec2<T> newPoint(mVec.x * c - mVec.y * s, mVec.x * s + mVec.y * c);
			mVec = newPoint + mCenter;
		}
		template<typename T> inline void nullify(Vec2<T>& mVec) { mVec.x = mVec.y = 0; }
		template<typename T> inline void normalize(Vec2<T>& mVec) { const T& m(getMagnitude(mVec)); if(m != 0) mVec /= m; }
		template<typename T> inline Vec2<T> getNormalized(Vec2<T> mVec) { normalize(mVec); return mVec; }

		// Resize a vec maintaining direction
		template<typename T> inline void resize(Vec2<T>& mVec, const T& mLength)	{ normalize(mVec); mVec *= mLength; }
		template<typename T> inline void getResized(Vec2<T> mVec, const T& mLength) { normalize(mVec); return mVec * mLength; }

		// Component-based vec clamping
		template<typename T> inline void cClamp(Vec2<T>& mVec, const T& mMin, const T& mMax)		{ ssvu::clamp(mVec.x, mMin, mMax); ssvu::clamp(mVec.y, mMin, mMax); }
		template<typename T> inline void cClampMin(Vec2<T>& mVec, const T& mMin)					{ ssvu::clampMin(mVec.x, mMin); ssvu::clampMin(mVec.y, mMin); }
		template<typename T> inline void cClampMax(Vec2<T>& mVec, const T& mMax)					{ ssvu::clampMax(mVec.x, mMax); ssvu::clampMax(mVec.y, mMax); }
		template<typename T> inline Vec2<T> getCClamped(Vec2<T> mVec, const T& mMin, const T& mMax)	{ cClamp(mVec, mMin, mMax); return mVec; }
		template<typename T> inline Vec2<T> getCClampedMin(Vec2<T> mVec, const T& mMin)				{ cClampMin(mVec, mMin); return mVec; }
		template<typename T> inline Vec2<T> getCClampedMax(Vec2<T> mVec, const T& mMax)				{ cClampMax(mVec, mMax); return mVec; }

		// Magnitude-based vec clamping
		template<typename T> inline void mClamp(Vec2<T>& mVec, const T& mMin, const T& mMax)		{ assert(mMin < mMax); const T& m(getMagnitude(mVec)); if(m < mMin) { resize(mVec, mMin); return; } if(m > mMax) { resize(mVec, mMax); return; } }
		template<typename T> inline void mClampMin(Vec2<T>& mVec, const T& mMin)					{ if(getMagnitude(mVec) < mMin) resize(mVec, mMin); }
		template<typename T> inline void mClampMax(Vec2<T>& mVec, const T& mMax)					{ if(getMagnitude(mVec) > mMax) resize(mVec, mMax); }
		template<typename T> inline Vec2<T> getMClamped(Vec2<T> mVec, const T& mMin, const T& mMax)	{ mClamp(mVec, mMin, mMax); return mVec; }
		template<typename T> inline Vec2<T> getMClampedMin(Vec2<T> mVec, const T& mMin)				{ mClampMin(mVec, mMin); return mVec; }
		template<typename T> inline Vec2<T> getMClampedMax(Vec2<T> mVec, const T& mMax)				{ mClampMax(mVec, mMax); return mVec; }

		// Get angle from vec direction
		template<typename T> inline T getRadians(Vec2<T> mVec) { normalize(mVec); return atan2(mVec.y, mVec.x); }
		template<typename T> inline T getDegrees(Vec2<T> mVec) { return ssvu::toDegrees(getRadians(mVec)); }

		// Get unit vec from angle
		template<typename T> inline Vec2<T> getVecFromRadians(T mRadians, T mMagnitude) { return Vec2<T>(mMagnitude * cos(mRadians), mMagnitude * sin(mRadians)); }
		template<typename T> inline Vec2<T> getVecFromDegrees(T mDegrees, T mMagnitude) { return getVecFromRadians(ssvu::toRadians(mDegrees), mMagnitude); }

		// Get direction between two vecs
		template<typename T> inline Vec2<T> getDirection(const Vec2<T>& mVec, const Vec2<T>& mTarget) { return getNormalized(mTarget - mVec); }

		// TODO: document
		template<typename T> inline void moveTowards(Vec2<T>& mVec, const Vec2<T>& mTarget, T mMagnitude) { mVec += getDirection(mVec, mTarget) * mMagnitude; }
		template<typename T> inline Vec2<T> getOrbitFromRadians(const Vec2<T>& mVec, T mRadians, T mRadius) { return mVec + Vec2<T>(cos(mRadians), sin(mRadians)) * mRadius; }
		template<typename T> inline Vec2<T> getOrbitFromDegrees(const Vec2<T>& mVec, T mDegrees, T mRadius) { return getOrbitFromRadians(mVec, ssvu::toRadians(mDegrees), mRadius); }
		template<typename T> inline Vec2<T> getMovedTowards(Vec2<T> mVec, const Vec2<T>& mTarget, T mMagnitude) { moveTowards(mVec, mTarget, mMagnitude); return mVec; }
		template<typename T> inline T getDotProduct(const Vec2<T>& mA, const Vec2<T>& mB) { return mA.x * mB.x + mA.y * mB.y; }
		template<typename T> inline Vec2<T> getRotatedAroundCenter(Vec2<T> mPoint, const Vec2<T>& mCenter, float mRadians) { rotateAroundCenter(mPoint, mCenter, mRadians); return mPoint; }
		template<typename T> inline T getDistanceEuclideanSquared(const Vec2<T>& mA, const Vec2<T>& mB)	{ return ssvu::getDistanceEuclideanSquared(mA.x, mA.y, mB.x, mB.y); }
		template<typename T> inline T getDistanceEuclidean(const Vec2<T>& mA, const Vec2<T>& mB)		{ return ssvu::getDistanceEuclidean(mA.x, mA.y, mB.x, mB.y); }

		inline void add2StateInput(GameState& mGameState, const Input::Trigger& mTrigger, bool& mValue, Input::Trigger::Type mType = Input::Trigger::Type::Always)
		{
			mGameState.addInput(mTrigger, [&](float){ mValue = true; }, [&](float){ mValue = false; }, mType);
		}
		inline void add3StateInput(GameState& mGameState, const Input::Trigger& mNegative, Input::Trigger mPositive, int& mValue, Input::Trigger::Type mType = Input::Trigger::Type::Always)
		{
			mGameState.addInput(mNegative, [&](float){ mValue = -1; },	[&](float){ if(mValue == -1) mValue = 0; }, mType);
			mGameState.addInput(mPositive, [&](float){ mValue = 1; },	[&](float){ if(mValue == 1) mValue = 0; }, mType);
		}
	}
}

#endif
