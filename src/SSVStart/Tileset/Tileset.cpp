// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Tileset/Tileset.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	Tileset::Tileset(Vector2i mTileSize) : tileSize{mTileSize} { }

	IntRect Tileset::getRect(int mX, int mY) const { return IntRect{mX * tileSize.x, mY * tileSize.y, tileSize.x, tileSize.y}; }
	IntRect Tileset::getRect(const string& mLabel) const { return getRect(labels.at(mLabel).x, labels.at(mLabel).y); }

	IntRect Tileset::operator[](const string& mLabel) const { return getRect(mLabel); }

	void Tileset::setLabel(const string& mLabel, int mX, int mY) { labels[mLabel] = {mX, mY}; }
}
