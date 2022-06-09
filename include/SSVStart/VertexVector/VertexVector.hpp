// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <vector>

namespace ssvs
{

template <sf::PrimitiveType TPrimitive>
struct VertexVector : public std::vector<sf::Vertex>, public sf::Drawable
{
    using std::vector<sf::Vertex>::vector;
    inline void draw(sf::RenderTarget& mRenderTarget,
        const sf::RenderStates& mRenderStates) const override
    {
        mRenderTarget.draw(
            this->data(), this->size(), TPrimitive, mRenderStates);
    }
};

} // namespace ssvs
