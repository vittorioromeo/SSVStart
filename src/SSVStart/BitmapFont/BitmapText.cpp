// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <iostream>
#include "SSVStart/BitmapFont/BitmapText.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	BitmapText::BitmapText(const BitmapFont& mBitmapFont, const string& mStr) : bitmapFont(mBitmapFont), texture(bitmapFont.getTexture()), str{mStr} { }

	void BitmapText::draw(RenderTarget& mRenderTarget, RenderStates mRenderStates) const
	{
		if(mustRecalculate) const_cast<BitmapText*>(this)->recalculate();
		mRenderStates.transform *= getTransform();
		mRenderStates.texture = &texture;
		mRenderTarget.draw(vertices, mRenderStates);
	}

	void BitmapText::setString(const string& mStr)		{ str = mStr; mustRecalculate = true; }
	void BitmapText::setColor(const Color& mColor)		{ color = mColor; for(unsigned int i{0}; i < vertices.getVertexCount(); ++i) vertices[i].color = color; }
	void BitmapText::setTracking(int mTracking)			{ tracking = mTracking; mustRecalculate = true; }

	const BitmapFont& BitmapText::getBitmapFont() const	{ return bitmapFont; }
	FloatRect BitmapText::getLocalBounds() const		{ return bounds; }
	FloatRect BitmapText::getGlobalBounds() const		{ return getTransform().transformRect(getLocalBounds()); }
	const string& BitmapText::getString() const			{ return str; }
	const Color& BitmapText::getColor() const			{ return color; }
	int BitmapText::getTracking() const					{ return tracking; }

	void BitmapText::recalculate()
	{
		const auto& width(bitmapFont.getCellWidth());
		const auto& height(bitmapFont.getCellHeight());
		unsigned int currentX{0}, currentY{0};

		vertices.clear();
		for(const auto& c : str)
		{
			switch(c)
			{
				case L'\t': currentX += 4; continue;
				case L'\n': ++currentY; currentX = 0; continue;
				case L'\v': currentY += 4; continue;
			}

			const auto& rect(bitmapFont.getGlyphRect(c));
			unsigned int spacing{tracking * currentX};

			vertices.append({Vector2f(currentX * width + spacing,		currentY * height),			color,	Vector2f(rect.left,					rect.top)});
			vertices.append({Vector2f((currentX + 1) * width + spacing,	currentY * height),			color,	Vector2f(rect.left + rect.width,	rect.top)});
			vertices.append({Vector2f((currentX + 1) * width + spacing,	(currentY + 1) * height),	color,	Vector2f(rect.left + rect.width,	rect.top + rect.height)});
			vertices.append({Vector2f(currentX * width + spacing,		(currentY + 1) * height),	color,	Vector2f(rect.left,					rect.top + rect.height)});
			++currentX;
		}

		mustRecalculate = false;
	}


}
