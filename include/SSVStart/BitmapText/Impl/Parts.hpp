// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_PARTS
#define SSVS_BITMAPTEXT_IMPL_PARTS

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextData.hpp"
#include "SSVStart/BitmapText/Impl/BitmapTextBase.hpp"

namespace ssvs
{
	class BTRPart
	{
		protected:
			BitmapTextRich& btr;
			std::vector<BTRPart*> children;
			bool enabled{true};

			inline void adopt(BTRPart& mX) { children.emplace_back(&mX); }

		public:
			inline BTRPart(BitmapTextRich& mBTR) noexcept : btr{mBTR} { }

			inline virtual void apply()				{ for(auto c : children) if(c->enabled) c->apply(); }
			inline virtual void update(FT mFT)		{ for(auto c : children) if(c->enabled) c->update(mFT); }

			inline void clear()
			{
				for(auto c : children) c->clear();
				children.clear();
			}

			template<typename T, typename... TArgs> auto& mk(TArgs&&... mArgs);
			template<typename T, typename... TArgs> auto& mk(T*& mTarget, TArgs&&... mArgs);

			auto& operator<<(BTRPart&);
			auto& operator<<(const std::string& mX);
			auto& operator<<(std::string&& mX);
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
			template<typename T> inline BTRPString(BitmapTextRich& mBTR, T&& mStr) : BTRPart{mBTR}, str{ssvu::fwd<T>(mStr)} { }
			void apply() override;
			inline void update(FT mFT) override
			{
				BTRPart::update(mFT);
			}

			template<typename T> void setStr(T&& mX);
	};

	class BTRPColorFG : public BTRPart
	{
		public:
			enum class Anim{None, Pulse};

		private:
			sf::Color color, computed;
			float pulse{0.f}, pulseSpeed, pulseMax;
			Anim anim{Anim::None};

		public:
			inline BTRPColorFG(BitmapTextRich& mBTR, const sf::Color& mColor) : BTRPart{mBTR}, color{mColor}, computed{color} { }
			void apply() override;
			void update(FT mFT) override;

			void setColor(const sf::Color& mX);

			inline void setAnimNone() noexcept { anim = Anim::None; }
			inline void setAnimPulse(float mPulseSpeed, float mPulseMax, float mPulseStart = 0.f) noexcept
			{
				anim = Anim::Pulse;
				pulse = mPulseStart;
				pulseSpeed = mPulseSpeed;
				pulseMax = mPulseMax;
			}
	};

	class BTRPTracking : public BTRPart
	{
		private:
			float tracking;

		public:
			inline BTRPTracking(BitmapTextRich& mBTR, float mTracking) : BTRPart{mBTR}, tracking{mTracking} { }
			void apply() override;
			inline void update(FT mFT) override
			{
				BTRPart::update(mFT);
			}

			void setTracking(float mX);
	};

	namespace BTRP
	{
		using Group = BTRPart;
		using Str = BTRPString;
		using Trk = BTRPTracking;
		using ClFG = BTRPColorFG;
	}
}

#endif
