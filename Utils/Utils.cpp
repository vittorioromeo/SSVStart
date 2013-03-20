// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "Utils/Utils.h"

using namespace ssvu;
using namespace std;
using namespace sf;

namespace ssvs
{
	namespace Utils
	{
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
		
		void waitFor(ThreadWrapper& mThreadWrapper, Time mTime) { while(!mThreadWrapper.getFinished()) sleep(mTime); }

		using Request = Http::Request;
		using Response = Http::Response;
		using Status = Http::Response::Status;

		Response getGetResponse(const string& mHost, const string& mHostFolder, const string& mRequestFile)
		{
			return Http(mHost).sendRequest({mHostFolder + mRequestFile});
		}
		Response getPostResponse(const string& mHost, const string& mHostFolder, const string& mRequestFile, const string& mBody)
		{
			return Http(mHost).sendRequest({mHostFolder + mRequestFile, Request::Post, mBody});
		}
	}
}
