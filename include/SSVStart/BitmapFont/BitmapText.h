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
			bool mustRecalculate{true};

			void recalculate()
			{
				const auto& width(bitmapFont.getCellWidth());
				const auto& height(bitmapFont.getCellHeight());
				unsigned int iX{0}, iY{0};

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

					vertices.append({Vec2f(iX * width + spacing,		iY * height),		color,	Vec2f(rect.left,				rect.top)});
					vertices.append({Vec2f((iX + 1) * width + spacing,	iY * height),		color,	Vec2f(rect.left + rect.width,	rect.top)});
					vertices.append({Vec2f((iX + 1) * width + spacing,	(iY + 1) * height),	color,	Vec2f(rect.left + rect.width,	rect.top + rect.height)});
					vertices.append({Vec2f(iX * width + spacing,		(iY + 1) * height),	color,	Vec2f(rect.left,				rect.top + rect.height)});
					++iX;
				}

				mustRecalculate = false;
			}

		public:
			BitmapText(const BitmapFont& mBitmapFont, const std::string& mStr = "") : bitmapFont(mBitmapFont), texture(bitmapFont.getTexture()), str{mStr} { }

			inline void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override
			{
				if(mustRecalculate) const_cast<BitmapText*>(this)->recalculate();
				mRenderStates.transform *= getTransform();
				mRenderStates.texture = &texture;
				mRenderTarget.draw(vertices, mRenderStates);
			}

			inline void setString(const std::string& mStr)	{ str = mStr; mustRecalculate = true; }
			inline void setColor(const sf::Color& mColor)	{ color = mColor; for(auto i(0u); i < vertices.getVertexCount(); ++i) vertices[i].color = color; }
			inline void setTracking(int mTracking)			{ tracking = mTracking; mustRecalculate = true; }

			inline const BitmapFont& getBitmapFont() const	{ return bitmapFont; }
			inline sf::FloatRect getLocalBounds() const		{ return bounds; }
			inline sf::FloatRect getGlobalBounds() const	{ return getTransform().transformRect(getLocalBounds()); }
			inline const std::string& getString() const		{ return str; }
			inline const sf::Color& getColor() const		{ return color; }
			inline int getTracking() const					{ return tracking; }
	};
}

#endif
