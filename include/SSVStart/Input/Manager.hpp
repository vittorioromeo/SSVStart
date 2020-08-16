// Copyright (c) 2013-2015 Vittorio Romeo
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
            std::vector<std::unique_ptr<Bind>> binds;
            bool isIgnoring{false}, mustSort{false};

        public:
            inline void update(InputState& mInputState, FT mFT)
            {
                for(auto& b : binds)
                {
                    b->update(mFT, mInputState);

                    // Some special input combos, such as ALT+ENTER
                    // (fullscreen),
                    // may work best if all the other inputs are then ignored.
                    if(isIgnoring) break;
                }
            }
            inline void refresh(InputState& mInputState)
            {
                if(mustSort)
                {
                    std::sort(std::begin(binds), std::end(binds), [](const auto& mA, const auto& mB)
                        {
                            return *mA < *mB;
                        });
                    mustSort = false;
                }

                isIgnoring = false;
                processedInput.reset();
                for(auto& b : binds) b->refresh(mInputState);
            }
            template <typename... TArgs>
            inline Bind& emplace(TArgs&&... mArgs)
            {
                auto& result = binds.emplace_back(std::make_unique<Bind>(*this, FWD(mArgs)...));
                mustSort = true;
                return *result;
            }
            
            inline void refreshTriggers(Trigger trigger, Tid bindID)
            {
                for(auto& b : binds)
                    if(b->getTriggerID() == bindID)
                        b->refreshTrigger(trigger);
            }

            inline void ignoreNextInputs() noexcept { isIgnoring = true; }
        };
    }
}

#endif
