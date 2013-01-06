/* The MIT License (MIT)
 * Copyright (c) 2012 Vittorio Romeo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UTILS_H_SSVS
#define UTILS_H_SSVS

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Timeline/Timeline.h"
#include <SFML/Graphics.hpp>

namespace ssvs
{
	// Randomness
	int getRnd(int, int);


	template<typename T> std::string toStr(const T &t) { std::ostringstream oss; oss << t; return std::string(oss.str()); }
	template<typename T> void easyErase(std::vector<T>& mVector, T& mItem) { mVector.erase(std::remove(std::begin(mVector), std::end(mVector), mItem), std::end(mVector)); }
	template<typename T> int getSign(T mValue) { if (mValue > 0) return 1; else return -1; }
	template<typename T> T clamp(const T& value, const T& low, const T& high) { return value < low ? low : (value > high ? high : value); }
	template<typename T> int countNewLines(T mValue) { int result{0}; for(auto c : mValue) if (c == '\n') result++; return result; }
	template<typename T> T toRadians(const T mValue) { return mValue / 57.3f; }


	float getSaturated(float);
	float getSmootherStep(float, float, float);
	bool isPointInPolygon(std::vector<sf::Vector2f*>, sf::Vector2f);

	sf::Vector2f getOrbit(const sf::Vector2f&, const float, const float);
	sf::Vector2f getNormalized(const sf::Vector2f);
	void movePointTowardsCenter(sf::Vector2f &mVector, const sf::Vector2f mCenter, const float mSpeed);

	void clearAndResetTimeline(Timeline& mTimeline);
}

#endif /* UTILS_H_SSVS */
