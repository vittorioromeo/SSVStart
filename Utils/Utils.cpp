#include "Utils.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	namespace Utils
	{
		int countNewLines(const string& mString) { int result{0}; for(auto c : mString) if(c == '\n') result++; return result; }
		string replace(const string& mString, const string& mFrom, const string& mTo)
		{
			string result{mString};
			size_t start_pos = result.find(mFrom);
			if(start_pos == string::npos) return result;
			result.replace(start_pos, mFrom.length(), mTo);
			return result;
		}
		bool endsWith(const string &mString, const string &mEnding)
		{
			if(mString.length() >= mEnding.length()) return (0 == mString.compare (mString.length() - mEnding.length(), mEnding.length(), mEnding));
			return false;
		}
		string toLower(const string &mString) { string result{mString}; transform(begin(result), end(result), begin(result), ::tolower); return result; }

		int getRnd(int min, int max)
		{
		   double x = rand()/static_cast<double>(RAND_MAX);
		   int that = min + static_cast<int>( x * (max - min) );
		   return that;
		}


		float getSaturated(float x) { return std::max(0.0f, std::min(1.0f, x)); }
		float getSmootherStep(float edge0, float edge1, float x)
		{
			x = getSaturated((x - edge0)/(edge1 - edge0));
			return x*x*x*(x*(x*6 - 15) + 10);
		}
		bool isPointInPolygon(vector<Vector2f*> verts, Vector2f test)
		{
			size_t nvert{verts.size()};
			size_t i, j;
			bool c{0};

			for (i = 0, j = nvert-1; i < nvert; j = i++)
				if(((verts[i]->y>test.y) != (verts[j]->y>test.y)) && (test.x < (verts[j]->x-verts[i]->x) * (test.y-verts[i]->y) / (verts[j]->y-verts[i]->y) + verts[i]->x))
					c = !c;

			return c;
		}

		Vector2f getOrbit(const Vector2f& mParent, const float mDegrees, const float mRadius)
		{
			return Vector2f{mParent.x + cos(toRadians(mDegrees)) * mRadius, mParent.y + sin(toRadians(mDegrees)) * mRadius};
		}
		void movePointTowardsCenter(Vector2f &mVector, const Vector2f mCenter, const float mSpeed)
		{
			Vector2f m{mCenter - mVector};
			m = getNormalized(m) * mSpeed;
			mVector += m;
		}
		void clearAndResetTimeline(Timeline& mTimeline) { mTimeline.clear(); mTimeline.reset(); }
	}
}
