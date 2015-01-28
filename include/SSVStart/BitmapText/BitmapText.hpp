// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT
#define SSVS_BITMAPTEXT

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/BitmapFont.hpp"
#include "SSVStart/VertexVector/VertexVector.hpp"

namespace ssvs
{
	class BitmapTextRich;

	namespace Impl
	{
		struct BitmapTextData
		{
			unsigned int iX, iY, width, height;
			float xMin, xMax, yMin, yMax;
			float tracking{0.f};
			sf::Color colorFG{sf::Color::White};

			inline void reset(const BitmapFont& mBF)
			{
				iX = iY = 0;
				width = mBF.getCellWidth();
				height = mBF.getCellHeight();

				xMin = xMax = yMin = yMax = 0;
			}
		};

		template<typename TC, typename TB> inline void strToVertices(const BitmapFont& mBitmapFont, const std::string& mStr, BitmapTextData& mD, TC& mVertices, TB& mBounds)
		{
			for(const auto& c : mStr)
			{
				switch(c)
				{
					case L'\t': mD.iX += 4;			continue;
					case L'\n': ++mD.iY; mD.iX = 0;	continue;
					case L'\v': mD.iY += 4;			continue;
				}

				const auto& rect(mBitmapFont.getGlyphRect(c));
				float spacing{mD.tracking * mD.iX};

				float gLeft(mD.iX * mD.width + spacing);		if(mD.xMin > gLeft) mD.xMin = gLeft;
				float gRight((mD.iX + 1) * mD.width + spacing);	if(mD.xMax < gRight) mD.xMax = gRight;
				float gTop(mD.iY * mD.height);					if(mD.yMin > gTop) mD.yMin = gTop;
				float gBottom((mD.iY + 1) * mD.height);			if(mD.yMax < gBottom) mD.yMax = gBottom;

				mVertices.emplace_back(Vec2f{gLeft, gTop},		mD.colorFG,	Vec2f(rect.left,				rect.top));
				mVertices.emplace_back(Vec2f{gRight, gTop},		mD.colorFG,	Vec2f(rect.left + rect.width,	rect.top));
				mVertices.emplace_back(Vec2f{gRight, gBottom},	mD.colorFG,	Vec2f(rect.left + rect.width,	rect.top + rect.height));
				mVertices.emplace_back(Vec2f{gLeft, gBottom},	mD.colorFG,	Vec2f(rect.left,				rect.top + rect.height));

				++mD.iX;
			}

			mBounds = {mD.xMin, mD.yMin, mD.xMax - mD.xMin, mD.yMax - mD.yMin};
		}
	}

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
				inline BitmapTextBase(const BitmapFont& mBitmapFont) : bitmapFont{&mBitmapFont}, texture{&bitmapFont->getTexture()} { }

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

	class BitmapText : public Impl::BitmapTextBase<BitmapText>
	{
		template<typename> friend class Impl::BitmapTextBase;

		private:
			std::string str;
			mutable bool mustRefreshGeometry{true}, mustRefreshColor{true};

			inline void refresh() const
			{
				refreshGeometry();
				refreshColor();
			}
			inline void refreshGeometry() const
			{
				if(!mustRefreshGeometry) return;
				SSVU_ASSERT(bitmapFont != nullptr);

				bdd.reset(*bitmapFont);

				vertices.clear();
				Impl::strToVertices(*bitmapFont, str, bdd, vertices, bounds);

				mustRefreshGeometry = false;
			}
			inline void refreshColor() const
			{
				if(!mustRefreshColor) return;
				for(auto& v : vertices) v.color = bdd.colorFG;
				mustRefreshColor = false;
			}

		public:
			inline BitmapText() : Impl::BitmapTextBase<BitmapText>{}  { }
			inline BitmapText(const BitmapFont& mBitmapFont, std::string mStr = "") : Impl::BitmapTextBase<BitmapText>{mBitmapFont}, str{mStr} { }

			// Sink setters
			inline void setString(const std::string& mStr)		{ str = mStr; mustRefreshGeometry = true; }
			inline void setString(std::string&& mStr) noexcept	{ str = std::move(mStr); mustRefreshGeometry = true; }

			inline void setColor(const sf::Color& mColor)	{ bdd.colorFG = mColor; mustRefreshColor = true; }
			inline void setTracking(float mTracking)		{ bdd.tracking = mTracking; mustRefreshGeometry = true; }

			inline const auto& getString() const noexcept	{ return str; }

	};

	class BTRPart
	{
		protected:
			BitmapTextRich& btr;
			std::vector<BTRPart*> children;
			bool enabled{true};

			template<typename T, typename... TArgs> auto& addImpl(TArgs&&... mArgs);

		public:
			inline BTRPart(BitmapTextRich& mBTR) noexcept : btr{mBTR} { }
			inline virtual void apply();

			auto& addGroup();
			auto& addStr(const std::string& mX);
			auto& addColorFG(const sf::Color& mX);
			auto& addTracking(float mX);

			auto& operator<<(const std::string& mX);
			auto& operator<<(const sf::Color& mX);

			void setEnabled(bool mX) noexcept;
	};

	using PartRecycler = ssvu::PolyRecycler<BTRPart>;
	using PartPtr = typename ssvu::PolyRecycler<BTRPart>::PtrType;

	class BTRPString : public BTRPart
	{
		private:
			std::string str;

		public:
			inline BTRPString(BitmapTextRich& mBTR, const std::string& mStr) : BTRPart{mBTR}, str{mStr} { }
			inline void apply() override;

			template<typename T> void setStr(T&& mX);
	};

	class BTRPColorFG : public BTRPart
	{
		private:
			sf::Color color;

		public:
			inline BTRPColorFG(BitmapTextRich& mBTR, const sf::Color& mColor) : BTRPart{mBTR}, color{mColor} { }
			inline void apply() override;

			void setColor(const sf::Color& mX);
	};

	class BTRPTracking : public BTRPart
	{
		private:
			float tracking;

		public:
			inline BTRPTracking(BitmapTextRich& mBTR, float mTracking) : BTRPart{mBTR}, tracking{mTracking} { }
			inline void apply() override;

			void setTracking(float mX);
	};

	// TODO: testing, better code, move to files, update(float)?
	class BitmapTextRich : public Impl::BitmapTextBase<BitmapTextRich>
	{
		template<typename> friend class Impl::BitmapTextBase;

		friend class BTRPart;
		friend class BTRPString;
		friend class BTRPColorFG;
		friend class BTRPTracking;

		private:
			PartRecycler partRecycler;
			std::vector<PartPtr> partManager;
			BTRPart* basePart;
			mutable bool mustRefresh{true};

			inline void refresh() const
			{
				if(!mustRefresh) return;
				mustRefresh = false;

				SSVU_ASSERT(bitmapFont != nullptr);
				vertices.clear();

				bdd.reset(*bitmapFont);

				bdd.tracking = 0.f;
				bdd.colorFG = sf::Color::White;

				basePart->apply();
			}

			inline void applyStr(const std::string& mStr) const { Impl::strToVertices(*bitmapFont, mStr, bdd, vertices, bounds); }
			inline void applyColorFG(const sf::Color& mColor) const { bdd.colorFG = mColor; }
			inline void applyTracking(float mTracking) const { bdd.tracking = mTracking; }

			template<typename T, typename... TArgs> inline auto& createPart(TArgs&&... mArgs)
			{
				return partRecycler.getCreateEmplace<T>(partManager, *this, ssvu::fwd<TArgs>(mArgs)...);
			}

		public:
			inline BitmapTextRich()
			{
				basePart = &createPart<BTRPart>();
			}
			inline BitmapTextRich(const BitmapFont& mBitmapFont) : Impl::BitmapTextBase<BitmapTextRich>{mBitmapFont}
			{
				basePart = &createPart<BTRPart>();
			}

			BTRPart& addGroup();
			BTRPString& addStr(const std::string& mX);
			BTRPColorFG& addColorFG(const sf::Color& mX);
			BTRPTracking& addTracking(float mX);

			auto& operator<<(const std::string& mX);
			auto& operator<<(const sf::Color& mX);
	};

	inline void BTRPart::apply()
	{
		for(auto c : children) if(c->enabled) c->apply();
	}
	inline void BTRPart::setEnabled(bool mX) noexcept
	{
		if(enabled != mX) btr.refresh();
		enabled = mX;

		for(auto c : children) c->setEnabled(mX);
	}

	template<typename T, typename... TArgs> inline auto& BTRPart::addImpl(TArgs&&... mArgs)
	{
		auto& result(btr.createPart<T>(ssvu::fwd<TArgs>(mArgs)...));
		children.emplace_back(&result);
		return result;
	}

	inline auto& BTRPart::addGroup()						{ return addImpl<BTRPart>(); }
	inline auto& BTRPart::addStr(const std::string& mX)		{ return addImpl<BTRPString>(mX); }
	inline auto& BTRPart::addColorFG(const sf::Color& mX)	{ return addImpl<BTRPColorFG>(mX); }
	inline auto& BTRPart::addTracking(float mX)				{ return addImpl<BTRPTracking>(mX); }

	inline auto& BTRPart::operator<<(const std::string& mX)	{ addStr(mX); return *this; }
	inline auto& BTRPart::operator<<(const sf::Color& mX)	{ addColorFG(mX); return *this; }

	inline void BTRPString::apply() { btr.applyStr(str); BTRPart::apply(); }
	template<typename T> inline void BTRPString::setStr(T&& mX)
	{
		if(str != mX) btr.mustRefresh = true;
		str = ssvu::fwd<T>(mX);
	}

	inline void BTRPColorFG::apply() { btr.applyColorFG(color); BTRPart::apply(); }
	inline void BTRPColorFG::setColor(const sf::Color& mX)
	{
		if(color != mX) btr.mustRefresh = true;
		color = mX;
	}

	inline void BTRPTracking::apply() { btr.applyTracking(tracking); BTRPart::apply(); }
	inline void BTRPTracking::setTracking(float mX)
	{
		if(tracking != mX) btr.mustRefresh = true;
		tracking = mX;
	}

	inline BTRPart& BitmapTextRich::addGroup()							{ return basePart->addGroup(); }
	inline BTRPString& BitmapTextRich::addStr(const std::string& mX)	{ return basePart->addStr(mX); }
	inline BTRPColorFG& BitmapTextRich::addColorFG(const sf::Color& mX)	{ return basePart->addColorFG(mX); }
	inline BTRPTracking& BitmapTextRich::addTracking(float mX)			{ return basePart->addTracking(mX); }

	inline auto& BitmapTextRich::operator<<(const std::string& mX)	{ addStr(mX); return *this; }
	inline auto& BitmapTextRich::operator<<(const sf::Color& mX)	{ addColorFG(mX); return *this; }
}

#endif
