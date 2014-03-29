// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_MANAGER
#define SSVS_INPUT_MANAGER

#include <vector>
#include <functional>
#include "SSVStart/Input/Bind.hpp"
#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	namespace Input
	{
		class InputState;
		class Combo;

		class Manager
		{
			friend class Combo;

			private:
				KeyBitset processedKeys;
				BtnBitset processedBtns;
				std::vector<ssvu::Uptr<Bind>> binds;

			public:
				inline void update(InputState& mInputState, FT mFT) { for(auto& b : binds) b->update(*this, mFT, mInputState); }
				inline void refresh(InputState& mInputState)
				{
					processedKeys.reset(); processedBtns.reset();
					for(auto& b : binds) b->refresh(*this, mInputState);
				}
				template<typename... TArgs> inline Bind& emplace(TArgs&&... mArgs)
				{
					auto& result(ssvu::getEmplaceUptr<Bind>(binds, std::forward<TArgs>(mArgs)...));
					ssvu::sort(binds); return result;
				}
		};
	}
}

#endif
