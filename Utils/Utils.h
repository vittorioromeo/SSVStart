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
#include "Timeline/Timeline.h"
#include "Utils/ThreadWrapper.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

namespace ssvs
{
	namespace Utils
	{
		// std::string
		template<typename T> std::string toStr(const T &mValue) { std::ostringstream oss; oss << mValue; return std::string(oss.str()); }
		int countNewLines(const std::string& mString);
		std::string replace(const std::string& mString, const std::string& mFrom, const std::string& mTo);
		std::string replaceAll(const std::string& mString, const std::string& mFrom, const std::string& mTo);
		bool startsWith(const std::string& mString, const std::string& mStart);
		bool endsWith(const std::string &mString, const std::string &mEnding);
		std::string toLower(const std::string &mString);
		std::vector<std::string> split(const std::string& mString, char mSplitter, bool mKeepSplitter = false);

		// Collections
		template<typename T, typename V> void eraseRemove(T& mItems, const V& mValue) { mItems.erase(std::remove(std::begin(mItems), std::end(mItems), mValue), std::end(mItems)); }
		template<typename T, typename V> bool contains(const T& mItems, const V& mValue) { return std::find(std::begin(mItems), std::end(mItems), mValue) != std::end(mItems); }
		template<typename T, typename T2> bool containsAny(T& mItems, const T2& mValues) { for(auto& value : mValues) if(contains(mItems, value)) return true; return false; }

		// std::map
		template<typename K, typename V>std::vector<K> getKeys(std::map<K, V> mMap)
		{
			std::vector<K> result;
			for(auto itr = mMap.begin(); itr != mMap.end(); ++itr) result.push_back(itr->first);
			return result;
		}

		// Maths
		template<typename T> constexpr int getSign(const T& mValue) { return mValue > 0 ? 1 : -1; }
		template<typename T> constexpr T clamp(const T& mValue, const T& mLow, const T& mHigh) { return mValue < mLow ? mLow : (mValue > mHigh ? mHigh : mValue); }
		float getSaturated(float);
		float getSmootherStep(float, float, float);

		// Angles
		template<typename T> constexpr T toRadians(const T& mValue) { return mValue / 57.3f; }
		template<typename T> constexpr T toDegrees(const T& mValue) { return mValue * 57.3f; }
		template<typename T> T wrapRadians(const T& mValue) { T result = fmod(mValue, 6.28f); if(result < 0) result += 6.28f; return result; }
		template<typename T> T wrapDegrees(const T& mValue) { T result = fmod(mValue, 360.f); if(result < 0) result += 360.f; return result; }
		template<typename T> T getRadiansToPoint(const sf::Vector2<T>& mStart, const sf::Vector2<T>& mEnd) { return atan2(mEnd.y - mStart.y, mEnd.x - mStart.x); }
		template<typename T> T getDegreesToPoint(const sf::Vector2<T>& mStart, const sf::Vector2<T>& mEnd) { return toDegrees(atan2(mEnd.y - mStart.y, mEnd.x - mStart.x)); }
		template<typename T, typename J> T getRotatedRadians(const T& mStart, const T& mEnd, const J& mSpeed) { T start = wrapRadians(mStart), end = wrapRadians(mEnd); if(abs(start - end) < mSpeed) return end; return wrapRadians(start + (sin(end - start))*mSpeed); }
		template<typename T, typename J> T getRotatedDegrees(const T& mStart, const T& mEnd, const J& mSpeed) { T start = wrapDegrees(mStart), end = wrapDegrees(mEnd); if(abs(start - end) < mSpeed) return end; return wrapDegrees(start + (sin((end - start)/57.3f))*mSpeed); }

		// Random
		int getRnd(int, int);

		// Collision
		bool isPointInPolygon(std::vector<sf::Vector2f*>, sf::Vector2f);

		// Vectors
		template<typename T> T getMagnitude(const sf::Vector2<T>& mVector) { return sqrt(mVector.x * mVector.x + mVector.y * mVector.y); }
		template<typename T> sf::Vector2<T> getNormalized(const sf::Vector2<T>& mVector) { T m = getMagnitude(mVector); return {mVector.x / m, mVector.y / m}; }
		template<typename T> T getRadians(const sf::Vector2<T>& mVector) { auto n = getNormalized(mVector); return atan2(n.y, n.x); }
		template<typename T> T getDegrees(const sf::Vector2<T>& mVector) { return toDegrees(getRadians(mVector)); }
		template<typename T> sf::Vector2<T> getVectorFromRadians(T mRadians, T mMagnitude) { return sf::Vector2<T>(mMagnitude * cos(mRadians), mMagnitude * sin(mRadians)); }
		template<typename T> sf::Vector2<T> getVectorFromDegrees(T mDegrees, T mMagnitude) { return getVectorFromRadians(toRadians(mDegrees), mMagnitude); }
		sf::Vector2f getOrbit(const sf::Vector2f&, const float, const float);
		void movePointTowardsCenter(sf::Vector2f &mVector, const sf::Vector2f mCenter, const float mSpeed);

		// Timelines
		void clearAndResetTimeline(Timeline& mTimeline);

		// ThreadWrapper
		void waitFor(ThreadWrapper& mThreadWrapper, sf::Time mTime = sf::milliseconds(10));

		// sf::Network
		sf::Http::Response getGetResponse(const std::string& mHost, const std::string& mHostFolder, const std::string& mRequestFile);
		sf::Http::Response getPostResponse(const std::string& mHost, const std::string& mHostFolder, const std::string& mRequestFile, const std::string& mBody);
	}
}

#endif
