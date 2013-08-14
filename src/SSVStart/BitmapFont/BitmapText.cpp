// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/BitmapFont/BitmapText.h"
#include "SSVStart/Global/Typedefs.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	void BitmapText::draw(RenderTarget& mRenderTarget, RenderStates mRenderStates) const
	{
		if(mustRecalculate) const_cast<BitmapText*>(this)->recalculate();
		mRenderStates.transform *= getTransform();
		mRenderStates.texture = &texture;
		mRenderTarget.draw(vertices, mRenderStates);
	}

	void BitmapText::recalculate()
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
}
