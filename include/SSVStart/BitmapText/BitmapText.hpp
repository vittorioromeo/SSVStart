// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT
#define SSVS_BITMAPTEXT

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/BitmapFont.hpp"
#include "SSVStart/VertexVector/VertexVector.hpp"

namespace ssvs
{
	class BitmapText : public sf::Transformable, public sf::Drawable
	{
		private:
			const BitmapFont* bitmapFont{nullptr};
			const sf::Texture* texture{nullptr};
			std::string str;
			mutable ssvs::VertexVector<sf::PrimitiveType::Quads> vertices;
			mutable sf::FloatRect bounds;
			sf::Color color{sf::Color::White};
			float tracking{0};
			mutable bool mustRefreshGeometry{true}, mustRefreshColor{true};

			inline void refreshGeometry() const
			{
				if(!mustRefreshGeometry) return;

				SSVU_ASSERT(bitmapFont != nullptr);

				unsigned int iX{0}, iY{0}, width{bitmapFont->getCellWidth()}, height{bitmapFont->getCellHeight()};
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

					const auto& rect(bitmapFont->getGlyphRect(c));
					float spacing{tracking * iX};

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
			inline BitmapText() { }
			inline BitmapText(const BitmapFont& mBitmapFont, std::string mStr = "") : bitmapFont{&mBitmapFont}, texture{&bitmapFont->getTexture()}, str{std::move(mStr)} { }

			inline void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override
			{
				SSVU_ASSERT(bitmapFont != nullptr && texture != nullptr);

				refreshGeometry(); refreshColor();
				mRenderStates.transform *= getTransform();
				mRenderStates.texture = texture;
				mRenderTarget.draw(vertices, mRenderStates);
			}

			// Sink setters
			inline void setString(const std::string& mStr)		{ str = mStr; mustRefreshGeometry = true; }
			inline void setString(std::string&& mStr) noexcept	{ str = std::move(mStr); mustRefreshGeometry = true; }

			inline void setColor(const sf::Color& mColor)	{ color = mColor; mustRefreshColor = true; }
			inline void setTracking(float mTracking)		{ tracking = mTracking; mustRefreshGeometry = true; }

			inline const auto& getBitmapFont() const noexcept	{ return bitmapFont; }
			inline const auto& getString() const noexcept		{ return str; }
			inline const auto& getColor() const noexcept		{ return color; }
			inline auto getTracking() const noexcept			{ return tracking; }
			inline const auto& getLocalBounds() const			{ refreshGeometry(); return bounds; }
			inline auto getGlobalBounds() const					{ return getTransform().transformRect(getLocalBounds()); }
	};
}

#endif
