// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Tileset/Tileset.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	Tileset::Tileset(Vector2u mTileSize) : tileSize{mTileSize} { }

	Vector2u Tileset::getIndex(const string& mLabel) const			{ return labels.at(mLabel); }
	IntRect Tileset::operator[](Vector2u mIndex) const				{ return IntRect(mIndex.x * tileSize.x, mIndex.y * tileSize.y, tileSize.x, tileSize.y); }
	void Tileset::setLabel(const string& mLabel, Vector2u mIndex)	{ labels[mLabel] = mIndex; }
}
