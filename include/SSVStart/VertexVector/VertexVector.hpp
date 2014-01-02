// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_VERTEXVECTOR
#define SSVS_VERTEXVECTOR

#include <vector>
#include <SFML/Graphics.hpp>

namespace ssvs
{
	template<sf::PrimitiveType TPrimitive> struct VertexVector : public std::vector<sf::Vertex>, public sf::Drawable
	{
		using std::vector<sf::Vertex>::vector;
		inline void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override
		{
			mRenderTarget.draw(&this->operator[](0), this->size(), TPrimitive, mRenderStates);
		}
	};
}

#endif
