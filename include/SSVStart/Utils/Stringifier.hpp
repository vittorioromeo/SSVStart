// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_STRINGIFIER
#define SSVS_UTILS_STRINGIFIER

#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Input/Combo.hpp"
#include "SSVStart/Input/Trigger.hpp"
#include "SSVStart/Utils/Input.hpp"

namespace ssvu
{
	template<typename T> struct Stringifier<ssvs::Vec2<T>>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const ssvs::Vec2<T>& mX)
		{
			Impl::printBold<TFmt>(mStream, "(");
			Impl::callStringifyImpl<TFmt>(mStream, mX.x);
			Impl::printBold<TFmt>(mStream, "; ");
			Impl::callStringifyImpl<TFmt>(mStream, mX.y);
			Impl::printBold<TFmt>(mStream, ")");
		}
	};

	template<typename T> struct Stringifier<sf::Rect<T>>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const sf::Rect<T>& mX)
		{
			Impl::printBold<TFmt>(mStream, "R((");
			Impl::callStringifyImpl<TFmt>(mStream, mX.left);
			Impl::printBold<TFmt>(mStream, "; ");
			Impl::callStringifyImpl<TFmt>(mStream, mX.top);
			Impl::printBold<TFmt>(mStream, ")[");
			Impl::callStringifyImpl<TFmt>(mStream, mX.width);
			Impl::printBold<TFmt>(mStream, "; ");
			Impl::callStringifyImpl<TFmt>(mStream, mX.height);
			Impl::printBold<TFmt>(mStream, "])");
		}
	};

	template<> struct Stringifier<sf::Color>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const sf::Color& mX)
		{
			Impl::printBold<TFmt>(mStream, "(");
			Impl::printNonBold<TFmt>(mStream, toInt(mX.r), Console::Color::Red);
			Impl::printBold<TFmt>(mStream, ", ");
			Impl::printNonBold<TFmt>(mStream, toInt(mX.g), Console::Color::Green);
			Impl::printBold<TFmt>(mStream, ", ");
			Impl::printNonBold<TFmt>(mStream, toInt(mX.b), Console::Color::Blue);
			Impl::printBold<TFmt>(mStream, ", ");
			Impl::printNonBold<TFmt>(mStream, toInt(mX.a));
			Impl::printBold<TFmt>(mStream, ")");
		}
	};

	template<> struct Stringifier<ssvs::KKey>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const ssvs::KKey& mX)
		{
			Impl::printNonBold<TFmt>(mStream, "(" + ssvs::getKKeyName(mX) + ")", Console::Color::Yellow);
		}
	};

	template<> struct Stringifier<ssvs::MBtn>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const ssvs::MBtn& mX)
		{
			Impl::printNonBold<TFmt>(mStream, "(" + ssvs::getMBtnName(mX) + ")", Console::Color::Green);
		}
	};

	template<> struct Stringifier<ssvs::Input::Combo>
	{
		using T = ssvs::Input::Combo;
		template<bool TFmt> inline static void impl(std::ostream& mStream, const T& mX)
		{
			mStream << "[";

			int added{0}, total(mX.getKeys().count() + mX.getBtns().count());

			for(auto i(0u); i < mX.getKeys().size(); ++i)
			{
				if(mX.getKeys()[i])
				{
					++added;
					Impl::callStringifyImpl<TFmt>(mStream, ssvs::KKey(i - 1));
					mStream << ((added >= total) ? "" : ", ");
				}
			}

			for(auto i(0u); i < mX.getBtns().size(); ++i)
			{
				if(mX.getBtns()[i])
				{
					++added;
					Impl::callStringifyImpl<TFmt>(mStream, ssvs::MBtn(i - 1));
					mStream << ((added >= total) ? "" : ", ");
				}
			}

			mStream << "]";
		}
	};

	template<> struct Stringifier<ssvs::Input::Trigger>
	{
		using T = ssvs::Input::Trigger;
		template<bool TFmt> inline static void impl(std::ostream& mStream, const T& mX)
		{
			mStream << "{";
			for(auto i(0u); i < mX.getCombos().size(); ++i)
			{
				Impl::callStringifyImpl<TFmt>(mStream, mX.getCombos()[i]);
				mStream << ((i == mX.getCombos().size() - 1) ? "" : ", ");
			}
			mStream << "}";
		}
	};
}

#endif
