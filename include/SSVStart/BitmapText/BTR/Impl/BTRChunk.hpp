// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTRCHUNK
#define SSVS_BITMAPTEXT_BTR_IMPL_BTRCHUNK

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/Ptr.hpp"
#include "SSVStart/BitmapText/BTR/Impl/Fwd.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"

#include <SSVUtils/MemoryManager/MemoryManager.hpp>

#include <cassert>

namespace ssvs
{
    namespace BTR
    {
        namespace Impl
        {
            class BTRChunk
            {
                template <typename>
                friend struct Impl::EffectHelper;
                friend class Impl::BTRRoot;

            private:
                BTRRoot& root;
                Ptr<BTRChunk> parent{nullptr};
                std::string str;
                std::vector<Ptr<BTREffect>> childrenEffects;
                std::vector<Ptr<BTRChunk>> children;
                float modTracking{0.f}, modLeading{0.f}, modHChunkSpacing{0.f};
                std::size_t idxHierarchyBegin, idxHierarchyEnd;
                bool enabled{true};

                template <typename... TArgs>
                BTRChunk& mkChild(TArgs&&... mArgs);
                template <typename T, typename... TArgs>
                T& mkEffect(TArgs&&... mArgs);

                void refreshGeometry() noexcept;
                void refreshEffects() noexcept;

                template <bool TSelf = false, typename TF>
                inline void recurseParents(const TF& mFn) const
                {
                    if(TSelf) mFn(*this);

                    auto p(parent);
                    while(p != nullptr && p->enabled)
                    {
                        mFn(*p);
                        p = p->parent;
                    }
                }

                template <bool TSelf = false, typename TF>
                inline void recurseChildren(const TF& mFn)
                {
                    if(TSelf) mFn(*this);
                    for(auto& c : children)
                        if(c->enabled) c->recurseChildren<true>(mFn);
                }

                inline void update(FT mFT) noexcept
                {
                    for(auto& e : childrenEffects) e->update(mFT);
                    for(auto& c : children)
                        if(c->enabled) c->update(mFT);
                }

            public:
                inline BTRChunk(BTRRoot& mRoot) noexcept : root{mRoot} {}

                inline auto getTracking() const noexcept SSVU_ATTRIBUTE(pure)
                {
                    float result{0.f};
                    recurseParents([&result](const auto& mP)
                        {
                            result += mP.modTracking;
                        });
                    return result;
                }
                inline auto getLeading() const noexcept SSVU_ATTRIBUTE(pure)
                {
                    float result{0.f};
                    recurseParents([&result](const auto& mP)
                        {
                            result += mP.modLeading;
                        });
                    return result;
                }
                inline auto getHChunkSpacing() const noexcept SSVU_ATTRIBUTE(pure)
                {
                    float result{0.f};
                    recurseParents([&result](const auto& mP)
                        {
                            result += mP.modHChunkSpacing;
                        });
                    return result;
                }

                template <typename TF>
                void forVertices(TF mFn) noexcept;

                template <typename T>
                void setStr(T&& mX);
                inline const auto& getStr() const noexcept { return str; }

                inline void setEnabled(bool mX) noexcept { enabled = mX; }
                inline bool isEnabled() const noexcept { return enabled; }

                // Make children and go one level deeper
                auto& in();
                auto& in(Ptr<BTRChunk>&);
                template <typename T>
                auto& in(T&& mStr);
                template <typename T>
                auto& in(Ptr<BTRChunk>&, T&& mStr);

                // Make children and stay on the same level
                auto& mk(Ptr<BTRChunk>&);
                template <typename T>
                auto& mk(T&& mStr);
                template <typename T>
                auto& mk(Ptr<BTRChunk>&, T&& mStr);

                // Add effects
                auto& eff(const sf::Color&);
                template <typename T, typename... TArgs>
                auto& eff(TArgs&&...);
                template <typename T, typename... TArgs>
                auto& eff(Ptr<T>&, TArgs&&...);

                // Go back one level
                inline auto& out() noexcept
                {
                    assert(parent != nullptr);
                    return *parent;
                }
                inline const auto& out() const noexcept
                {
                    assert(parent != nullptr);
                    return *parent;
                }
            };

            using BTRChunkRecVector = ssvu::MonoRecVector<BTRChunk>;
            using BTREffectRecVector = ssvu::PolyRecVector<BTREffect>;
        }
    }
}

#endif
