#ifndef UTILS_H_SSVS
#define UTILS_H_SSVS

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

namespace ssvs
{
	template<class T>
	string toStr(const T &t)
	{
		ostringstream oss;
		oss << t;
		return string(oss.str());
	}

	template <class T>
	void delFromVector(vector<T>& mVector, T mItem)
	{
		mVector.erase(remove(mVector.begin(), mVector.end(), mItem), mVector.end());
	}
}

#endif /* UTILS_H_SSVS */
