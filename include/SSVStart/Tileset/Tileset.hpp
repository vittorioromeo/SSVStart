// Copyright (c) 2013-2014 Vittorio Romeo
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
		SSVS_JSON_CNV_FRIEND();
		SSVJ_CNV_FRIEND();

		private:
			Vec2u tileSize;
			std::unordered_map<std::string, Vec2u> labels;

		public:
			inline Tileset() = default;
			inline Tileset(const Vec2u& mTileSize) noexcept : tileSize{mTileSize} { }

			inline void setTileSize(const Vec2u& mTileSize) noexcept			{ tileSize = mTileSize; }
			inline void setLabel(const std::string& mLabel, const Vec2u& mIdx)	{ labels[mLabel] = mIdx; }

			inline const auto& getLabels() const noexcept				{ return labels; }
			inline const auto& getTileSize() const noexcept				{ return tileSize; }
			inline const auto& getIdx(const std::string& mLabel) const	{ return labels.at(mLabel); }

			inline auto operator()(unsigned int mX, unsigned int mY) const noexcept	{ return sf::IntRect(mX * tileSize.x, mY * tileSize.y, tileSize.x, tileSize.y); }
			inline auto operator()(const Vec2u& mIdx) const noexcept				{ return (*this)(mIdx.x, mIdx.y); }
			inline auto operator()(const std::string& mLabel) const noexcept		{ return (*this)(getIdx(mLabel)); }
	};
}

#endif
