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
#include "SSVStart/Utils/ThreadWrapper.h"
#include "SSVStart/GameSystem/GameState.h"
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	namespace Utils
	{
		// Angles
		template<typename T> T getRadiansTowards(const Vec2<T>& mVec, const Vec2<T>& mTarget) { return atan2(mTarget.y - mVec.y, mTarget.x - mVec.x); }
		template<typename T> T getDegreesTowards(const Vec2<T>& mVec, const Vec2<T>& mTarget) { return ssvu::toDegrees(getRadiansToPoint(mVec, mTarget)); }

		// Collision
		bool isPointInPolygon(const std::vector<Vec2f>& mVertices, Vec2f mPoint);

		// Vecs
		template<typename T> void rotateAroundCenter(Vec2<T>& mPoint, const Vec2<T>& mCenter, float mRadians)
		{
			float s(sin(mRadians)), c(cos(mRadians));
			mPoint -= mCenter;
			Vec2<T> newPoint(mPoint.x * c - mPoint.y * s, mPoint.x * s + mPoint.y * c);
			mPoint = newPoint + mCenter;
		}
		template<typename T> T getMagnitude(const Vec2<T>& mVec) { return sqrt(mVec.x * mVec.x + mVec.y * mVec.y); }
		template<typename T> Vec2<T> getNormalized(const Vec2<T>& mVec) { T m(getMagnitude(mVec)); return m == 0 ? mVec : Vec2<T>{mVec.x / m, mVec.y / m}; }
		template<typename T> T getRadians(const Vec2<T>& mVec) { auto n(getNormalized(mVec)); return atan2(n.y, n.x); }
		template<typename T> T getDegrees(const Vec2<T>& mVec) { return ssvu::toDegrees(getRadians(mVec)); }
		template<typename T> Vec2<T> getVecFromRadians(T mRadians, T mMagnitude) { return Vec2<T>(mMagnitude * cos(mRadians), mMagnitude * sin(mRadians)); }
		template<typename T> Vec2<T> getVecFromDegrees(T mDegrees, T mMagnitude) { return getVecFromRadians(ssvu::toRadians(mDegrees), mMagnitude); }
		template<typename T> Vec2<T> getOrbitFromRadians(const Vec2<T>& mVec, T mRadians, T mRadius) { return mVec + Vec2<T>(cos(mRadians), sin(mRadians)) * mRadius; }
		template<typename T> Vec2<T> getOrbitFromDegrees(const Vec2<T>& mVec, T mDegrees, T mRadius) { return getOrbitFromRadians(mVec, ssvu::toRadians(mDegrees), mRadius); }
		template<typename T> Vec2<T> getDirection(const Vec2<T>& mVec, const Vec2<T>& mTarget) { return getNormalized(mTarget - mVec); }
		template<typename T> Vec2<T> getMovedTowards(const Vec2<T>& mVec, const Vec2<T>& mTarget, T mMagnitude) { return mVec + getDirection(mVec, mTarget) * mMagnitude; }
		template<typename T> T getDotProduct(const Vec2<T>& mA, const Vec2<T>& mB) { return mA.x * mB.x + mA.y * mB.y; }
		template<typename T> Vec2<T> getRotatedAroundCenter(Vec2<T> mPoint, const Vec2<T>& mCenter, float mRadians) { rotateAroundCenter(mPoint, mCenter, mRadians); return mPoint; }

		// ThreadWrapper
		void waitFor(ThreadWrapper& mThreadWrapper, sf::Time mTime = sf::milliseconds(1));

		// Quick state input additions
		void add2StateInput(GameState& mGameState, const Input::Trigger& mTrigger, bool& mValue);
		void add3StateInput(GameState& mGameState, const Input::Trigger& mNegative, Input::Trigger mPositive, int& mValue);
	}
}

#endif
