// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPTEXTBASE
#define SSVS_BITMAPTEXT_IMPL_BITMAPTEXTBASE

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/VertexVector/VertexVector.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextDrawState.hpp"

namespace ssvs
{
	namespace Impl
	{
		template<typename TDerived> class BitmapTextBase : public sf::Transformable, public sf::Drawable
		{
			private:
				inline auto& getTD() noexcept				{ return ssvu::castUp<TDerived>(*this); }
				inline const auto& getTD() const noexcept	{ return ssvu::castUp<TDerived>(*this); }

			protected:
				const BitmapFont* bitmapFont{nullptr};
				const sf::Texture* texture{nullptr};
				mutable ssvs::VertexVector<sf::PrimitiveType::Quads> vertices;
				mutable sf::FloatRect bounds;
				mutable Impl::BitmapTextDrawState bdd;

				mutable SizeT rowCellCount;
				mutable std::vector<SizeT> rowCells;
				float alignMultiplier{0.f};

				inline BitmapTextBase() noexcept { }
				inline BitmapTextBase(const BitmapFont& mBF) : bitmapFont{&mBF}, texture{&bitmapFont->getTexture()} { }

				inline void setAlign(TextAlign mX) noexcept { alignMultiplier = static_cast<float>(static_cast<int>(mX)) * 0.5f; }

				inline void refreshStart() const
				{
					SSVU_ASSERT(bitmapFont != nullptr);

					rowCellCount = 0;
					rowCells.clear();
					vertices.clear();
					bdd.reset(*bitmapFont);
				}

				inline void createVertices(const std::string& mStr) const
				{
					vertices.reserve(mStr.size() * 4);

					for(const auto& c : mStr)
					{
						switch(c)
						{
							case L'\t': bdd.iX += 4;											continue;
							case L'\n': ++bdd.iY; rowCells.emplace_back(bdd.iX); bdd.iX = 0;	continue;
							case L'\v': bdd.iY += 4;											continue;
						}

						const auto& rect(bitmapFont->getGlyphRect(c));
						auto spacing(bdd.tracking * bdd.iX);

						auto gLeft(bdd.iX * bdd.width + spacing );			ssvu::clampMax(bdd.xMin, gLeft);
						auto gRight((bdd.iX + 1) * bdd.width + spacing);	ssvu::clampMin(bdd.xMax, gRight);
						auto gTop(bdd.iY * bdd.height);						ssvu::clampMax(bdd.yMin, gTop);
						auto gBottom((bdd.iY + 1) * bdd.height);			ssvu::clampMin(bdd.yMax, gBottom);

						vertices.emplace_back(Vec2f(gLeft, gTop),		bdd.colorFG,	Vec2f(rect.left,				rect.top));
						vertices.emplace_back(Vec2f(gRight, gTop),		bdd.colorFG,	Vec2f(rect.left + rect.width,	rect.top));
						vertices.emplace_back(Vec2f(gRight, gBottom),	bdd.colorFG,	Vec2f(rect.left + rect.width,	rect.top + rect.height));
						vertices.emplace_back(Vec2f(gLeft, gBottom),	bdd.colorFG,	Vec2f(rect.left,				rect.top + rect.height));

						++bdd.iX;
					}
				}

				inline void refreshFinish() const
				{
					// Recalculate bounds
					auto width(bdd.xMax - bdd.xMin);
					bounds = {bdd.xMin, bdd.yMin, width, bdd.yMax - bdd.yMin};

					// Add current row to `rowCells`, return if its the only one
					if(rowCells.empty()) return;
					rowCells.emplace_back(bdd.iX);

					SizeT lastVIdx{0};

					for(auto rc : rowCells)
					{
						auto vIdx(lastVIdx);

						// Find out the width of the current row
						auto targetVIdx(lastVIdx + rc * 4);
						float maxX{0.f};
						for(; vIdx < targetVIdx; vIdx += 4) maxX = std::max({maxX, vertices[vIdx].position.x, vertices[vIdx + 1].position.x});

						// Apply horizontal alignment
						auto offset(width - maxX);
						for(; lastVIdx < vIdx; ++lastVIdx) vertices[lastVIdx].position.x += offset * alignMultiplier;
					}
				}

			public:
				inline void update(FT)
				{
				}

				inline void draw(sf::RenderTarget& mRenderTarget, sf::RenderStates mRenderStates) const override
				{
					SSVU_ASSERT(bitmapFont != nullptr && texture != nullptr);

					getTD().refresh();
					mRenderStates.texture = texture;

					/*
					sf::RectangleShape rs;
					rs.setSize(Vec2f{bounds.width, bounds.height});
					rs.setPosition(Vec2f(getPosition()));
					rs.setFillColor(sf::Color{255, 0, 0, 150});
					rs.setOrigin(getOrigin());

					mRenderTarget.draw(rs, mRenderStates);
					*/


					mRenderStates.transform *= getTransform();
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
