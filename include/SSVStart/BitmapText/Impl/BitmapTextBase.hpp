// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPTEXTBASE
#define SSVS_BITMAPTEXT_IMPL_BITMAPTEXTBASE

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/VertexVector/VertexVector.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextData.hpp"

namespace ssvs
{
	namespace Impl
	{
		template<typename TDerived> class BitmapTextBase : public sf::Transformable, public sf::Drawable
		{
			private:
				inline auto& getTD() noexcept { return ssvu::castUp<TDerived>(*this); }
				inline const auto& getTD() const noexcept { return ssvu::castUp<TDerived>(*this); }

			protected:
				const BitmapFont* bitmapFont{nullptr};
				const sf::Texture* texture{nullptr};
				mutable ssvs::VertexVector<sf::PrimitiveType::Quads> vertices;
				mutable sf::FloatRect bounds;
				mutable Impl::BitmapTextData bdd;

				inline BitmapTextBase() { }
				inline BitmapTextBase(const BitmapFont& mBF) : bitmapFont{&mBF}, texture{&bitmapFont->getTexture()} { }
/*
				inline auto getMaxRowCells(const std::string& mStr) const
				{
					SizeT max{0}, currentMax{0};

					for(const auto& c : mStr)
					{
						switch(c)
						{
							case L'\t': currentMax += 4;									continue;
							case L'\n': max = std::max(max, currentMax); currentMax = 0;	continue;
							default: ++currentMax;											continue;
						}
					}

					return std::max(max, currentMax);
				}

				inline auto getRowOffsets(const std::string& mStr) const
				{
					auto maxCellsX(getMaxRowCells(mStr));

					std::vector<float> result;

					SizeT currentRow{0};

					for(const auto& c : mStr)
					{
						switch(c)
						{
							case L'\t': currentRow += 4; continue;
							case L'\n':
							{
								auto diff(maxCellsX - currentRow);
								result.emplace_back((diff * bitmapFont->getCellWidth()) / 2.f);
								currentRow = 0;
								continue;
							}
							default: ++currentRow; continue;
						}
					}

					auto diff(maxCellsX - currentRow);
					result.emplace_back((diff * bitmapFont->getCellWidth()) / 2.f);

					return result;
				}
*/
				inline void createVertices(const std::string& mStr) const
				{
					vertices.reserve(mStr.size() * 4);

					/*
					auto rowOffsets(getRowOffsets(mStr));
					ssvu::lo() << rowOffsets << "\n\n";
					SizeT currentRow{0};
					*/

					for(const auto& c : mStr)
					{
						//const auto& ro(rowOffsets[currentRow]);


						switch(c)
						{
							case L'\t': bdd.iX += 4;						continue;
							case L'\n': ++bdd.iY; bdd.iX = 0; /*++currentRow;*/	continue;
							case L'\v': bdd.iY += 4;						continue;
						}

						const auto& rect(bitmapFont->getGlyphRect(c));
						auto spacing(bdd.tracking * bdd.iX);

						auto gLeft(bdd.iX * bdd.width + spacing);			ssvu::clampMax(bdd.xMin, gLeft);
						auto gRight((bdd.iX + 1) * bdd.width + spacing);	ssvu::clampMin(bdd.xMax, gRight);
						auto gTop(bdd.iY * bdd.height);						ssvu::clampMax(bdd.yMin, gTop);
						auto gBottom((bdd.iY + 1) * bdd.height);			ssvu::clampMin(bdd.yMax, gBottom);

						vertices.emplace_back(Vec2f(gLeft, gTop),		bdd.colorFG,	Vec2f(rect.left,				rect.top));
						vertices.emplace_back(Vec2f(gRight, gTop),		bdd.colorFG,	Vec2f(rect.left + rect.width,	rect.top));
						vertices.emplace_back(Vec2f(gRight, gBottom),	bdd.colorFG,	Vec2f(rect.left + rect.width,	rect.top + rect.height));
						vertices.emplace_back(Vec2f(gLeft, gBottom),	bdd.colorFG,	Vec2f(rect.left,				rect.top + rect.height));

						++bdd.iX;
					}

					bounds = {bdd.xMin, bdd.yMin, bdd.xMax - bdd.xMin, bdd.yMax - bdd.yMin};
				}

			public:
				inline void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override
				{
					SSVU_ASSERT(bitmapFont != nullptr && texture != nullptr);

					getTD().refresh();

					mRenderStates.transform *= getTransform();
					mRenderStates.texture = texture;
					mRenderTarget.draw(vertices, mRenderStates);
				}

				inline const auto& getBitmapFont() const noexcept	{ return bitmapFont; }
				inline const auto& getLocalBounds() const			{ getTD().refresh(); return bounds; }
				inline auto getGlobalBounds() const					{ return getTransform().transformRect(getLocalBounds()); }
				inline const auto& getColor() const noexcept		{ return bdd.colorFG; }
				inline auto getTracking() const noexcept			{ return bdd.tracking; }
		};
	}
}

#endif
