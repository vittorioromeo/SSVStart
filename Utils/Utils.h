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
#include <SSVStart.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace ssvs
{
	template<class T> string toStr(const T &t) { ostringstream oss; oss << t; return string(oss.str()); }
	template<class T> void delFromVector(vector<T>& mVector, T mItem) { mVector.erase(remove(begin(mVector), end(mVector), mItem), end(mVector)); }
	template<class T> int getSign(T mValue) { if (mValue > 0) return 1; else return -1; }
	template<class T> T clamp(const T& value, const T& low, const T& high) { return value < low ? low : (value > high ? high : value); }
	template<class T> int countNewLines(T mValue) { int result{0}; for(auto c : mValue) if (c == '\n') result++; return result; }
	template<class T> T toRadians(const T mValue) { return mValue / 57.3f; }

	int getRnd(int, int);
	float getSaturated(float);
	float getSmootherStep(float, float, float);
	bool isPointInPolygon(std::vector<Vector2f*>, Vector2f);

	Vector2f getOrbit(const Vector2f&, const float, const float);
	Vector2f getNormalized(const Vector2f);
	void movePointTowardsCenter(Vector2f &mVector, const Vector2f mCenter, const float mSpeed);

	void clearAndResetTimeline(Timeline& mTimeline);
}

#endif /* UTILS_H_SSVS */
