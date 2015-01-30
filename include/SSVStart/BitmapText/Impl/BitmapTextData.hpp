// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPTEXTDATA
#define SSVS_BITMAPTEXT_IMPL_BITMAPTEXTDATA

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

namespace ssvs
{
	class BitmapTextRich;

	namespace Impl
	{
		struct BitmapTextData
		{
			sf::Color colorFG{sf::Color::White};
			float xMin, xMax, yMin, yMax;
			float tracking{0.f};
			unsigned int iX, iY, width, height;

			inline void reset(const BitmapFont& mBF)
			{
				xMin = xMax = yMin = yMax = 0;
				iX = iY = 0;
				width = mBF.getCellWidth();
				height = mBF.getCellHeight();
			}
		};
	}

	enum class TextAlign : int{Left = 0, Center = 1, Right = 2};
}

#endif
