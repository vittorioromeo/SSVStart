// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT
#define SSVS_BITMAPTEXT

#include <string>
#include <SFML/Graphics.hpp>
#include "SSVStart/BitmapFont/BitmapFont.h"
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class BitmapText : public sf::Transformable, public sf::Drawable
	{
		private:
			const BitmapFont& bitmapFont;
			const sf::Texture& texture;
			std::string str;
			sf::VertexArray vertices{sf::PrimitiveType::Quads};
			sf::FloatRect bounds;
			sf::Color color{sf::Color::White};
			int tracking{0};
			bool mustRefreshGeometry{true}, mustRefreshColor{true};

			void refreshGeometry()
			{
				const auto& width(bitmapFont.getCellWidth());
				const auto& height(bitmapFont.getCellHeight());
				unsigned int iX{0}, iY{0};
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

					const auto& gLeft(iX * width + spacing);			if(xMin > gLeft) xMin = gLeft;
					const auto& gRight((iX + 1) * width + spacing);		if(xMax < gRight) xMax = gRight;
					const auto& gTop(iY * height);						if(yMin > gTop) yMin = gTop;
					const auto& gBottom((iY + 1) * height);				if(yMax < gBottom) yMax = gBottom;

					vertices.append({Vec2f(gLeft,	gTop),		color,	Vec2f(rect.left,				rect.top)});
					vertices.append({Vec2f(gRight,	gTop),		color,	Vec2f(rect.left + rect.width,	rect.top)});
					vertices.append({Vec2f(gRight,	gBottom),	color,	Vec2f(rect.left + rect.width,	rect.top + rect.height)});
					vertices.append({Vec2f(gLeft,	gBottom),	color,	Vec2f(rect.left,				rect.top + rect.height)});

					++iX;
				}

				bounds = {xMin, xMax - xMin, yMin, yMax - yMin};
				mustRefreshGeometry = false;
			}
			void refreshColor() { for(auto i(0u); i < vertices.getVertexCount(); ++i) vertices[i].color = color; mustRefreshColor = false; }
			void refresh() const
			{
				if(mustRefreshGeometry) const_cast<BitmapText*>(this)->refreshGeometry();
				if(mustRefreshColor) const_cast<BitmapText*>(this)->refreshColor();
			}

		public:
			BitmapText(const BitmapFont& mBitmapFont, const std::string& mStr = "") : bitmapFont(mBitmapFont), texture(bitmapFont.getTexture()), str{mStr} { }

			inline void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override
			{
				refresh();
				mRenderStates.transform *= getTransform();
				mRenderStates.texture = &texture;
				mRenderTarget.draw(vertices, mRenderStates);
			}

			inline void setString(const std::string& mStr)	{ str = mStr; mustRefreshGeometry = true; }
			inline void setColor(const sf::Color& mColor)	{ color = mColor; mustRefreshColor = true; }
			inline void setTracking(int mTracking)			{ tracking = mTracking; mustRefreshGeometry = true; }

			inline const BitmapFont& getBitmapFont() const	{ return bitmapFont; }
			inline sf::FloatRect getLocalBounds() const		{ refresh(); return bounds; }
			inline sf::FloatRect getGlobalBounds() const	{ return getTransform().transformRect(getLocalBounds()); }
			inline const std::string& getString() const		{ return str; }
			inline const sf::Color& getColor() const		{ return color; }
			inline int getTracking() const					{ return tracking; }
	};
}

#endif
