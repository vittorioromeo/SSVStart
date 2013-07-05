// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Utils/Utils.h"

using namespace ssvu;
using namespace std;
using namespace sf;

namespace ssvs
{
	namespace Utils
	{
		bool isPointInPolygon(const vector<Vector2f>& mVertices, Vector2f mPoint)
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

		void waitFor(ThreadWrapper& mThreadWrapper, Time mTime) { while(!mThreadWrapper.getFinished()) sleep(mTime); }

		void add2StateInput(GameState& mGameState, const Input::Trigger& mTrigger, bool& mValue)
		{
			mGameState.addInput(mTrigger, [&](float){ mValue = true; }, [&](float){ mValue = false; });
		}
		void add3StateInput(GameState& mGameState, const Input::Trigger& mNegative, Input::Trigger mPositive, int& mValue)
		{
			mGameState.addInput(mNegative, [&](float){ mValue = -1; }, [&](float){ if(mValue == -1) mValue = 0; });
			mGameState.addInput(mPositive, [&](float){ mValue = 1; }, [&](float){ if(mValue == 1) mValue = 0; });
		}
	}
}
