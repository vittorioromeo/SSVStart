// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT
#define SSVS_BITMAPTEXT

#include <string>
#include <SFML/Graphics.hpp>
#include "SSVStart/BitmapFont/BitmapFont.hpp"
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/VertexVector/VertexVector.hpp"

namespace ssvs
{
	class BitmapText : public sf::Transformable, public sf::Drawable
	{
		private:
			const BitmapFont& bitmapFont;
			const sf::Texture& texture;
			std::string str;
			mutable ssvs::VertexVector<sf::PrimitiveType::Quads> vertices;
			mutable sf::FloatRect bounds;
			sf::Color color{sf::Color::White};
			int tracking{0};
			mutable bool mustRefreshGeometry{true}, mustRefreshColor{true};

			inline void refreshGeometry() const
			{
				if(!mustRefreshGeometry) return;

				unsigned int iX{0}, iY{0}, width{bitmapFont.getCellWidth()}, height{bitmapFont.getCellHeight()};
				float xMin{0}, xMax{0}, yMin{0}, yMax{0};

				vertices.clear();
				for(const auto& c : str)
				{
					switch(c)
					{
						case L'\t': iX += 4;		continue;
						case L'\n': ++iY; iX = 0;	continue;
						case L'\v': iY += 4;		continue;
					}

					const auto& rect(bitmapFont.getGlyphRect(c));
					unsigned int spacing{tracking * iX};

					float gLeft(iX * width + spacing);			if(xMin > gLeft) xMin = gLeft;
					float gRight((iX + 1) * width + spacing);	if(xMax < gRight) xMax = gRight;
					float gTop(iY * height);					if(yMin > gTop) yMin = gTop;
					float gBottom((iY + 1) * height);			if(yMax < gBottom) yMax = gBottom;

					vertices.emplace_back(Vec2f{gLeft,	gTop},		color,	Vec2f(rect.left,				rect.top));
					vertices.emplace_back(Vec2f{gRight,	gTop},		color,	Vec2f(rect.left + rect.width,	rect.top));
					vertices.emplace_back(Vec2f{gRight,	gBottom},	color,	Vec2f(rect.left + rect.width,	rect.top + rect.height));
					vertices.emplace_back(Vec2f{gLeft,	gBottom},	color,	Vec2f(rect.left,				rect.top + rect.height));

					++iX;
				}

				bounds = {xMin, yMin, xMax - xMin, yMax - yMin};
				mustRefreshGeometry = false;
			}
			inline void refreshColor() const { if(!mustRefreshColor) return; for(auto& v : vertices) v.color = color; mustRefreshColor = false; }

		public:
			BitmapText(const BitmapFont& mBitmapFont, std::string mStr = "") : bitmapFont(mBitmapFont), texture(bitmapFont.getTexture()), str{std::move(mStr)} { }

			inline void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override
			{
				refreshGeometry(); refreshColor();
				mRenderStates.transform *= getTransform();
				mRenderStates.texture = &texture;
				mRenderTarget.draw(vertices, mRenderStates);
			}

			inline void setString(std::string mStr)	{ str = std::move(mStr); mustRefreshGeometry = true; }
			inline void setColor(sf::Color mColor)	{ color = std::move(mColor); mustRefreshColor = true; }
			inline void setTracking(int mTracking)	{ tracking = mTracking; mustRefreshGeometry = true; }

			inline const BitmapFont& getBitmapFont() const noexcept	{ return bitmapFont; }
			inline const std::string& getString() const noexcept	{ return str; }
			inline const sf::Color& getColor() const noexcept		{ return color; }
			inline int getTracking() const noexcept					{ return tracking; }
			inline const sf::FloatRect& getLocalBounds() const		{ refreshGeometry(); return bounds; }
			inline sf::FloatRect getGlobalBounds() const			{ return getTransform().transformRect(getLocalBounds()); }
	};
}

#endif
