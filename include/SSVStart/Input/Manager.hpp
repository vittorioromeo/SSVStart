// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_MANAGER
#define SSVS_INPUT_MANAGER

namespace ssvs
{
	namespace Input
	{
		class Combo;
		class Bind;

		class Manager
		{
			friend Combo;
			friend Bind;

			private:
				InputState processedInput;
				ssvu::VecUPtr<Bind> binds;
				bool isIgnoring{false}, mustSort{false};

			public:
				inline void update(InputState& mInputState, FT mFT)
				{
					for(auto& b : binds)
					{
						b->update(mFT, mInputState);

						// Some special input combos, such as ALT+ENTER (fullscreen), may work best if all the other inputs are then ignored.
						if(isIgnoring) break;
					}
				}
				inline void refresh(InputState& mInputState)
				{
					if(mustSort)
					{
						ssvu::sort(binds, [](const ssvu::UPtr<Bind>& mA, const ssvu::UPtr<Bind>& mB){ return *mA < *mB; });
						mustSort = false;
					}

					isIgnoring = false;
					processedInput.reset();
					for(auto& b : binds) b->refresh(mInputState);
				}
				template<typename... TArgs> inline Bind& emplace(TArgs&&... mArgs)
				{
					auto& result(ssvu::getEmplaceUPtr<Bind>(binds, *this, std::forward<TArgs>(mArgs)...));
					mustSort = true;
					return result;
				}

				inline void ignoreNextInputs() noexcept { isIgnoring = true; }
		};
	}
}

#endif
