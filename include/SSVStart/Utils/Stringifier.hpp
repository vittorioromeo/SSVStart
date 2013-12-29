// Copyright (c) 2013 Vittorio Romeo
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
		template<bool TFmt> inline static void impl(std::ostream& mStream, const ssvs::Vec2<T>& mValue)
		{
			Internal::printBold<TFmt>(mStream, "(");
			Internal::callStringifyImpl<TFmt>(mStream, mValue.x);
			Internal::printBold<TFmt>(mStream, "; ");
			Internal::callStringifyImpl<TFmt>(mStream, mValue.y);
			Internal::printBold<TFmt>(mStream, ")");
		}
	};
	template<> struct Stringifier<sf::Color>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const sf::Color& mValue)
		{
			Internal::printBold<TFmt>(mStream, "(");
			Internal::printNonBold<TFmt>(mStream, int(mValue.r), Console::Color::Red);
			Internal::printBold<TFmt>(mStream, ", ");
			Internal::printNonBold<TFmt>(mStream, int(mValue.g), Console::Color::Green);
			Internal::printBold<TFmt>(mStream, ", ");
			Internal::printNonBold<TFmt>(mStream, int(mValue.b), Console::Color::Blue);
			Internal::printBold<TFmt>(mStream, ", ");
			Internal::printNonBold<TFmt>(mStream, int(mValue.a));
			Internal::printBold<TFmt>(mStream, ")");
		}
	};

	template<> struct Stringifier<ssvs::KKey>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const ssvs::KKey& mValue)
		{
			Internal::printNonBold<TFmt>(mStream, "(" + ssvs::getKKeyName(mValue) + ")", Console::Color::Yellow);
		}
	};

	template<> struct Stringifier<ssvs::MBtn>
	{
		template<bool TFmt> inline static void impl(std::ostream& mStream, const ssvs::MBtn& mValue)
		{
			Internal::printNonBold<TFmt>(mStream, "(" + ssvs::getMBtnName(mValue) + ")", Console::Color::Green);
		}
	};

	template<> struct Stringifier<ssvs::Input::Combo>
	{
		using T = ssvs::Input::Combo;
		template<bool TFmt> inline static void impl(std::ostream& mStream, const T& mValue)
		{
			mStream << "[";

			int added{0}, total{mValue.getKeys().count() + mValue.getBtns().count()};

			for(auto i(0u); i < mValue.getKeys().size(); ++i)
			{
				if(mValue.getKeys()[i])
				{
					++added;
					Internal::callStringifyImpl<TFmt>(mStream, ssvs::KKey(i - 1));
					mStream << ((added >= total) ? "" : ", ");
				}
			}

			for(auto i(0u); i < mValue.getBtns().size(); ++i)
			{
				if(mValue.getBtns()[i])
				{
					++added;
					Internal::callStringifyImpl<TFmt>(mStream, ssvs::MBtn(i - 1));
					mStream << ((added >= total) ? "" : ", ");
				}
			}

			mStream << "]";
		}
	};

	template<> struct Stringifier<ssvs::Input::Trigger>
	{
		using T = ssvs::Input::Trigger;
		template<bool TFmt> inline static void impl(std::ostream& mStream, const T& mValue)
		{
			mStream << "{";
			for(auto i(0u); i < mValue.getCombos().size(); ++i)
			{
				Internal::callStringifyImpl<TFmt>(mStream, mValue.getCombos()[i]);
				mStream << ((i == mValue.getCombos().size() - 1) ? "" : ", ");
			}
			mStream << "}";
		}
	};
}

#endif
