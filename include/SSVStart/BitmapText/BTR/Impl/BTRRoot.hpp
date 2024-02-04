// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTRROOT
#define SSVS_BITMAPTEXT_BTR_IMPL_BTRROOT

#include "SSVStart/Global/Typedefs.hpp"

#include "SSVStart/BitmapText/Impl/BitmapTextDrawState.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREWave.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREColor.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRDrawState.hpp"

#include "SSVStart/VertexVector/VertexVector.hpp"

#include <SSVUtils/Core/Common/Frametime.hpp>
#include <SSVUtils/Core/Utils/Math.hpp>

#include <SSVUtils/MemoryManager/MemoryManager.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include <cassert>

namespace ssvs
{
namespace BTR
{
namespace Impl
{
class BTRRoot : public sf::Transformable, public sf::Drawable
{
    friend class BTR::Impl::BTRChunk;
    template <typename>
    friend struct BTR::Impl::EffectHelper;

private:
    const BitmapFont* bitmapFont{nullptr};
    const sf::Texture* texture{nullptr};
    mutable VertexVector<sf::PrimitiveType::Triangles> vertices,
        verticesOriginal;
    mutable sf::FloatRect bounds, globalBounds;
    mutable bool mustRefreshGeometry{true};

    BTRChunkRecVector chunks;
    BTREffectRecVector effects;

    Ptr<BTRChunk> baseChunk{&mkChunk()}, lastChunk{baseChunk};

    float alignMult{0.f};

    mutable BTRDrawState bdd;

    inline void refreshIfNeeded() const
    {
        refreshGeometryIfNeeded();
        baseChunk->refreshEffects();
    }

    inline void refreshGeometryIfNeeded() const
    {
        if(!mustRefreshGeometry) return;
        mustRefreshGeometry = false;

        refreshGeometryStart();
        baseChunk->refreshGeometry();
        verticesOriginal = vertices;
        refreshGeometryFinish();
    }

    template <typename... TArgs>
    inline BTRChunk& mkChunk(TArgs&&... mArgs)
    {
        auto& c(chunks.create(*this, FWD(mArgs)...));
        lastChunk = &c;
        return c;
    }
    template <typename T, typename... TArgs>
    inline T& mkEffect(TArgs&&... mArgs)
    {
        return effects.create<T>(FWD(mArgs)...);
    }

    inline void pushRowData() const
    {
        bdd.rDatas.emplace_back(vertices.back().position.x, bdd.iX);
    }

    inline void refreshGeometryStart() const noexcept
    {
        assert(bitmapFont != nullptr);

        vertices.clear();
        verticesOriginal.clear();
        bdd.reset(*bitmapFont);
    }

    inline void refreshGeometryFinish() const
    {
        // Push last row data
        pushRowData();

        // Recalculate bounds
        auto width(bdd.xMax - bdd.xMin);
        bounds = {{bdd.xMin, bdd.yMin}, {width, bdd.yMax - bdd.yMin}};
        globalBounds = getTransform().transformRect(bounds);

        // Apply horizontal alignment
        std::size_t lastVIdx{0};
        for(const auto& rd : bdd.rDatas)
        {
            auto targetVIdx(lastVIdx + rd.cells * 6);
            auto offset(width - rd.width);

            for(; lastVIdx < targetVIdx; ++lastVIdx)
                vertices[lastVIdx].position.x += offset * alignMult;
        }
    }

    inline void mkVertices(BTRChunk& mChunk) const
    {
        const auto& str(mChunk.str);
        bdd.nextHChunkSpacing = mChunk.getHChunkSpacing();
        mChunk.idxHierarchyBegin = vertices.size();

        for(const auto& c : str)
        {
            switch(c)
            {
                case L'\n': ++bdd.nl; continue;
                case L'\t': ++bdd.htab; continue;
                case L'\v': ++bdd.vtab; continue;
            }

            const auto& tracking(mChunk.getTracking());
            const auto& leading(mChunk.getLeading());
            const auto& rect(bitmapFont->getGlyphRect(c));

            auto newPos(vertices.empty() ? Vec2f(0.f, bdd.height)
                                         : vertices.back().position);

            newPos.x += bdd.nextHChunkSpacing;
            bdd.nextHChunkSpacing = 0.f;

            if(bdd.nl > 0)
            {
                pushRowData();

                bdd.iX = 0;
                newPos.x = 0;

                for(; bdd.nl > 0; --bdd.nl) newPos.y += bdd.height + leading;
            }

            newPos.x += tracking;
            for(; bdd.htab > 0; --bdd.htab)
                newPos.x += 4 * (bdd.width + tracking);
            for(; bdd.vtab > 0; --bdd.vtab)
                newPos.y += 4 * (bdd.height + leading);

            auto gLeft(newPos.x);
            auto gBottom(newPos.y);
            auto gRight(gLeft + bdd.width);
            auto gTop(gBottom - bdd.height);

            ssvu::clampMax(bdd.xMin, gLeft);
            ssvu::clampMin(bdd.xMax, gRight);
            ssvu::clampMax(bdd.yMin, gTop);
            ssvu::clampMin(bdd.yMax, gBottom);

            // NW
            vertices.emplace_back(
                Vec2f(gLeft, gTop), Vec2f(rect.left, rect.top));
            // SW
            vertices.emplace_back(Vec2f(gLeft, gBottom),
                Vec2f(rect.left, rect.top + rect.height));
            // SE
            vertices.emplace_back(Vec2f(gRight, gBottom),
                Vec2f(rect.left + rect.width, rect.top + rect.height));
            // NW
            vertices.emplace_back(
                Vec2f(gLeft, gTop), Vec2f(rect.left, rect.top));
            // SE
            vertices.emplace_back(Vec2f(gRight, gBottom),
                Vec2f(rect.left + rect.width, rect.top + rect.height));
            // NE
            vertices.emplace_back(
                Vec2f(gRight, gTop), Vec2f(rect.left + rect.width, rect.top));

            ++bdd.iX;
        }

        mChunk.idxHierarchyEnd = vertices.size();
    }

public:
    inline BTRRoot() noexcept
    {
    }
    inline BTRRoot(const BitmapFont& mBF) noexcept
        : bitmapFont{&mBF}, texture{&bitmapFont->getTexture()}
    {
    }

    inline void clear()
    {
        mustRefreshGeometry = true;
        chunks.clear();
        effects.clear();
        baseChunk = &mkChunk();
        lastChunk = baseChunk;
    }
    inline void update(ssvu::FT mFT) noexcept
    {
        baseChunk->update(mFT);
    }

    template <typename... TArgs>
    inline decltype(auto) in(TArgs&&... mArgs)
    {
        return baseChunk->in(FWD(mArgs)...);
    }
    template <typename T, typename... TArgs>
    inline decltype(auto) eff(TArgs&&... mArgs)
    {
        return baseChunk->eff<T>(FWD(mArgs)...);
    }

    inline void setAlign(TextAlign mX) noexcept
    {
        auto newAlignMult(ssvu::toFloat(ssvu::castEnum(mX)) * 0.5f);

        if(alignMult == newAlignMult) return;

        alignMult = newAlignMult;
        mustRefreshGeometry = true;
    }

    inline void draw(sf::RenderTarget& mRenderTarget,
        const sf::RenderStates& mRenderStates) const override
    {
        assert(bitmapFont != nullptr && texture != nullptr);

        refreshIfNeeded();

        auto rs = mRenderStates;
        rs.texture = texture;
        rs.transform *= getTransform();
        mRenderTarget.draw(vertices, rs);
    }

    inline auto& getRoot() noexcept
    {
        return *baseChunk;
    }
    inline auto& getLast() noexcept
    {
        return *lastChunk;
    }
    inline const auto& getRoot() const noexcept
    {
        return *baseChunk;
    }
    inline const auto& getLast() const noexcept
    {
        return *lastChunk;
    }

    inline const auto& getBitmapFont() const noexcept
    {
        return bitmapFont;
    }
    inline const auto& getLocalBounds() const
    {
        refreshGeometryIfNeeded();
        return bounds;
    }
    inline const auto& getGlobalBounds() const
    {
        refreshGeometryIfNeeded();
        return globalBounds;
    }
};
} // namespace Impl
} // namespace BTR
} // namespace ssvs

#endif
