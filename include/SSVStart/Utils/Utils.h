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
#include <SFML/Network.hpp>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Utils/ThreadWrapper.h"

namespace ssvs
{
	namespace Utils
	{
		// Angles
		template<typename T> T getRadiansToPoint(const sf::Vector2<T>& mStart, const sf::Vector2<T>& mEnd) { return atan2(mEnd.y - mStart.y, mEnd.x - mStart.x); }
		template<typename T> T getDegreesToPoint(const sf::Vector2<T>& mStart, const sf::Vector2<T>& mEnd) { return ssvu::toDegrees(getRadiansToPoint(mStart, mEnd)); }

		// Collision
		bool isPointInPolygon(const std::vector<sf::Vector2f>& mVertices, sf::Vector2f mPoint);

		// Vectors
		template<typename T> T getMagnitude(const sf::Vector2<T>& mVector) { return sqrt(mVector.x * mVector.x + mVector.y * mVector.y); }
		template<typename T> sf::Vector2<T> getNormalized(const sf::Vector2<T>& mVector) { T m(getMagnitude(mVector)); return {mVector.x / m, mVector.y / m}; }
		template<typename T> T getRadians(const sf::Vector2<T>& mVector) { auto n(getNormalized(mVector)); return atan2(n.y, n.x); }
		template<typename T> T getDegrees(const sf::Vector2<T>& mVector) { return ssvu::toDegrees(getRadians(mVector)); }
		template<typename T> sf::Vector2<T> getVectorFromRadians(T mRadians, T mMagnitude) { return sf::Vector2<T>(mMagnitude * cos(mRadians), mMagnitude * sin(mRadians)); }
		template<typename T> sf::Vector2<T> getVectorFromDegrees(T mDegrees, T mMagnitude) { return getVectorFromRadians(ssvu::toRadians(mDegrees), mMagnitude); }
		template<typename T> sf::Vector2<T> getOrbitFromRadians(const sf::Vector2<T>& mVector, T mRadians, T mRadius) { return mVector + sf::Vector2<T>(cos(mRadians), sin(mRadians)) * mRadius; }
		template<typename T> sf::Vector2<T> getOrbitFromDegrees(const sf::Vector2<T>& mVector, T mDegrees, T mRadius) { return getOrbitFromRadians(mVector, ssvu::toRadians(mDegrees), mRadius); }
		template<typename T> sf::Vector2<T> getDirection(const sf::Vector2<T>& mVector, const sf::Vector2<T>& mTarget) { return getNormalized(mTarget - mVector); }
		template<typename T> sf::Vector2<T> getTowards(const sf::Vector2<T>& mVector, const sf::Vector2<T>& mTarget, T mMagnitude) { return mVector + getDirection(mTarget, mVector) * mMagnitude; }

		// ThreadWrapper
		void waitFor(ThreadWrapper& mThreadWrapper, sf::Time mTime = sf::milliseconds(1));

		// sf::Network
		sf::Http::Response getGetResponse(const std::string& mHost, const std::string& mHostFolder, const std::string& mRequestFile);
		sf::Http::Response getPostResponse(const std::string& mHost, const std::string& mHostFolder, const std::string& mRequestFile, const std::string& mBody);
	}
}

#endif
