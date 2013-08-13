// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS
#define SSVS_UTILS

#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Global/Typedefs.h"

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
		bool isPointInPolygon(const std::vector<Vec2f>& mVertices, Vec2f mPoint);

		// Vec
		template<typename T> inline T getMagnitude(const Vec2<T>& mVec) { return sqrt(mVec.x * mVec.x + mVec.y * mVec.y); }
		template<typename T> void rotateAroundCenter(Vec2<T>& mVec, const Vec2<T>& mCenter, float mRadians)
		{
			float s(sin(mRadians)), c(cos(mRadians)); mVec -= mCenter;
			Vec2<T> newPoint(mVec.x * c - mVec.y * s, mVec.x * s + mVec.y * c);
			mVec = newPoint + mCenter;
		}
		template<typename T> inline void normalize(Vec2<T>& mVec) { T m(getMagnitude(mVec)); if(m != 0) mVec /= m; }
		template<typename T> inline Vec2<T> getNormalized(Vec2<T> mVec) { normalize(mVec); return mVec; }
		template<typename T> inline Vec2<T> getDirection(const Vec2<T>& mVec, const Vec2<T>& mTarget) { return getNormalized(mTarget - mVec); }
		template<typename T> inline void moveTowards(Vec2<T>& mVec, const Vec2<T>& mTarget, T mMagnitude) { mVec += getDirection(mVec, mTarget) * mMagnitude; }
		template<typename T> inline T getRadians(Vec2<T> mVec) { normalize(mVec); return atan2(mVec.y, mVec.x); }
		template<typename T> inline T getDegrees(Vec2<T> mVec) { return ssvu::toDegrees(getRadians(mVec)); }
		template<typename T> inline Vec2<T> getVecFromRadians(T mRadians, T mMagnitude) { return Vec2<T>(mMagnitude * cos(mRadians), mMagnitude * sin(mRadians)); }
		template<typename T> inline Vec2<T> getVecFromDegrees(T mDegrees, T mMagnitude) { return getVecFromRadians(ssvu::toRadians(mDegrees), mMagnitude); }
		template<typename T> inline Vec2<T> getOrbitFromRadians(const Vec2<T>& mVec, T mRadians, T mRadius) { return mVec + Vec2<T>(cos(mRadians), sin(mRadians)) * mRadius; }
		template<typename T> inline Vec2<T> getOrbitFromDegrees(const Vec2<T>& mVec, T mDegrees, T mRadius) { return getOrbitFromRadians(mVec, ssvu::toRadians(mDegrees), mRadius); }
		template<typename T> inline Vec2<T> getMovedTowards(Vec2<T> mVec, const Vec2<T>& mTarget, T mMagnitude) { moveTowards(mVec, mTarget, mMagnitude); return mVec; }
		template<typename T> inline T getDotProduct(const Vec2<T>& mA, const Vec2<T>& mB) { return mA.x * mB.x + mA.y * mB.y; }
		template<typename T> inline Vec2<T> getRotatedAroundCenter(Vec2<T> mPoint, const Vec2<T>& mCenter, float mRadians) { rotateAroundCenter(mPoint, mCenter, mRadians); return mPoint; }

		// Quick state input additions
		void add2StateInput(GameState& mGameState, const Input::Trigger& mTrigger, bool& mValue);
		void add3StateInput(GameState& mGameState, const Input::Trigger& mNegative, Input::Trigger mPositive, int& mValue);
	}
}

#endif
