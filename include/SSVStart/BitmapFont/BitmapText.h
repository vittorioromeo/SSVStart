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
			BitmapText(const BitmapFont& mBitmapFont, const std::string& mStr = "");

			void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override;

			sf::FloatRect getLocalBounds() const;
			sf::FloatRect getGlobalBounds() const;
			void setString(const std::string& mStr);
			void setColor(const sf::Color& mColor);
			void setTracking(int mTracking);

			const BitmapFont& getBitmapFont() const;
			const std::string& getString() const;
			int getTracking() const;
			const sf::Color& getColor() const;
	};
}

#endif
