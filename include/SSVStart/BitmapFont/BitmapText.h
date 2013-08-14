// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT
#define SSVS_BITMAPTEXT

#include <string>
#include <SFML/Graphics.hpp>
#include "SSVStart/BitmapFont/BitmapFont.h"

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

			void recalculate();

		public:
			BitmapText(const BitmapFont& mBitmapFont, const std::string& mStr = "") : bitmapFont(mBitmapFont), texture(bitmapFont.getTexture()), str{mStr} { }

			void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override;

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
