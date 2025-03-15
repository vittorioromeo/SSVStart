// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextDrawState.hpp"

#include <SSVUtils/Core/Utils/Math.hpp>
#include <SSVUtils/Core/Common/Casts.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Rect.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <vector>
#include <string>
#include <cstddef>
#include <cassert>

namespace ssvs::Impl {

template <typename TDerived>
class BitmapTextBase : public sf::Transformable
{
private:
    auto& getTD() noexcept
    {
        return ssvu::castUp<TDerived>(*this);
    }
    const auto& getTD() const noexcept
    {
        return ssvu::castUp<TDerived>(*this);
    }

protected:
    const BitmapFont* bitmapFont{nullptr};
    const sf::Texture* texture{nullptr};
    mutable std::vector<sf::Vertex> vertices;
    mutable sf::FloatRect bounds;
    mutable Impl::BitmapTextDrawState bdd;

    mutable std::vector<std::size_t> rowCells;
    float alignMultiplier{0.f};

    BitmapTextBase() = default;
    BitmapTextBase(const BitmapFont& mBF)
        : bitmapFont{&mBF}, texture{&bitmapFont->getTexture()}
    {}

    void setAlign(TextAlign mX) noexcept
    {
        alignMultiplier = ssvu::toFloat(ssvu::castEnum(mX)) * 0.5f;
    }

    void refreshGeometryStart() const
    {
        assert(bitmapFont != nullptr);

        rowCells.clear();
        vertices.clear();
        bdd.reset(*bitmapFont);
    }

    void createVertices(const std::string& mStr) const
    {
        vertices.reserve(mStr.size() * 6);

        for(const auto& c : mStr)
        {
            switch(c)
            {
                case L'\t': bdd.iX += 4; continue;
                case L'\v': bdd.iY += 4; continue;
                case L'\n':
                {
                    ++bdd.iY;
                    rowCells.emplace_back(bdd.chCount);
                    bdd.iX = bdd.chCount = 0;
                    continue;
                }
            }

            const sf::FloatRect rect(bitmapFont->getGlyphRect(c).to<sf::FloatRect>());
            auto spacing(bdd.tracking * bdd.iX);

            auto gLeft(bdd.iX * bdd.width + spacing);
            ssvu::clampMax(bdd.xMin, gLeft);
            auto gRight((bdd.iX + 1) * bdd.width + spacing);
            ssvu::clampMin(bdd.xMax, gRight);
            auto gTop(bdd.iY * bdd.height);
            ssvu::clampMax(bdd.yMin, gTop);
            auto gBottom((bdd.iY + 1) * bdd.height);
            ssvu::clampMin(bdd.yMax, gBottom);

            // NW
            vertices.emplace_back(
                sf::Vector2f(gLeft, gTop), bdd.colorFG, rect.position);
            // SW
            vertices.emplace_back(sf::Vector2f(gLeft, gBottom), bdd.colorFG,
                sf::Vector2f(rect.position.x, rect.position.y + rect.size.y));
            // SE
            vertices.emplace_back(sf::Vector2f(gRight, gBottom), bdd.colorFG,
                rect.position + rect.size);
            // NW
            vertices.emplace_back(
                sf::Vector2f(gLeft, gTop), bdd.colorFG, rect.position);
            // SE
            vertices.emplace_back(sf::Vector2f(gRight, gBottom), bdd.colorFG,
                rect.position + rect.size);
            // NE
            vertices.emplace_back(sf::Vector2f(gRight, gTop), bdd.colorFG,
                sf::Vector2f(rect.position.x + rect.size.x, rect.position.y));

            // Count printable characters in the current row.
            ++bdd.chCount;

            // Count all characters in the current row.
            ++bdd.iX;
        }
    }

    void refreshGeometryFinish() const
    {
        // Recalculate bounds
        auto width(bdd.xMax - bdd.xMin);
        bounds = {{bdd.xMin, bdd.yMin}, {width, bdd.yMax - bdd.yMin}};

        // Add current row to `rowCells`, return if its the only one
        if(rowCells.empty()) return;
        rowCells.emplace_back(bdd.iX);

        std::size_t lastVIdx{0};

        for(auto rc : rowCells)
        {
            auto vIdx(lastVIdx);

            // Find out the width of the current row
            auto targetVIdx(lastVIdx + rc * 4);
            float maxX{0.f};
            for(; vIdx < targetVIdx; vIdx += 4)
            {
                maxX = std::max({maxX, vertices[vIdx].position.x,
                    vertices[vIdx + 1].position.x});
            }

            // Apply horizontal alignment
            auto offset(width - maxX);
            for(; lastVIdx < vIdx; ++lastVIdx)
                vertices[lastVIdx].position.x += offset * alignMultiplier;
        }
    }

public:
    void draw(sf::RenderTarget& mRenderTarget,
        const sf::RenderStates& mRenderStates) const
    {
        assert(bitmapFont != nullptr && texture != nullptr);

        getTD().refreshIfNeeded();

        auto rs = mRenderStates;
        rs.texture = texture;
        rs.transform *= getTransform();
        mRenderTarget.draw(vertices, sf::PrimitiveType::Triangles, rs);
    }

    const auto& getBitmapFont() const noexcept
    {
        return bitmapFont;
    }
    const auto& getLocalBounds() const
    {
        getTD().refreshIfNeeded();
        return bounds;
    }
    auto getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }
    const auto& getColor() const noexcept
    {
        return bdd.colorFG;
    }
    auto getTracking() const noexcept
    {
        return bdd.tracking;
    }
};

} // namespace ssvs::Impl
