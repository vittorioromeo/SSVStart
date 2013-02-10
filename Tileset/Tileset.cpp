#include "Tileset.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	Tileset::Tileset(Vector2i mTileSize) : tileSize{mTileSize} { }

	Sprite Tileset::getSprite(int mX, int mY, const Texture& mTexture) { return Sprite{mTexture, getTextureRect(mX, mY)}; }
	Sprite Tileset::getSprite(const string& mLabel, const Texture& mTexture) { return Sprite{mTexture, getTextureRect(mLabel)}; }

	IntRect Tileset::getTextureRect(int mX, int mY) { return IntRect{mX * tileSize.x, mY * tileSize.y, tileSize.x, tileSize.y}; }
	IntRect Tileset::getTextureRect(const string& mLabel) { return getTextureRect(labels[mLabel].x, labels[mLabel].y); }

	void Tileset::setLabel(const string& mLabel, int mX, int mY) { labels[mLabel] = {mX, mY}; }
}

