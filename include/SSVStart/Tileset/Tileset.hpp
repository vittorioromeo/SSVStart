// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TILESET
#define SSVS_TILESET

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	class Tileset
	{
		private:
			Vec2u tileSize;
			std::unordered_map<std::string, Vec2u> labels;

		public:
			Tileset() = default;
			Tileset(const Vec2u& mTileSize) : tileSize{mTileSize} { }

			inline void setTileSize(const Vec2u& mTileSize) noexcept				{ tileSize = mTileSize; }
			inline void setLabel(const std::string& mLabel, const Vec2u& mIdx)		{ labels[mLabel] = mIdx; }

			inline const decltype(labels)& getLabels() const noexcept				{ return labels; }
			inline const Vec2u& getTileSize() const noexcept						{ return tileSize; }
			inline const Vec2u& getIdx(const std::string& mLabel) const				{ return labels.at(mLabel); }

			inline sf::IntRect operator()(unsigned int mX, unsigned int mY) const	{ return sf::IntRect(mX * tileSize.x, mY * tileSize.y, tileSize.x, tileSize.y); }
			inline sf::IntRect operator()(const Vec2u& mIdx) const					{ return (*this)(mIdx.x, mIdx.y); }
			inline sf::IntRect operator()(const std::string& mLabel) const			{ return (*this)(getIdx(mLabel)); }
	};
}

#endif
