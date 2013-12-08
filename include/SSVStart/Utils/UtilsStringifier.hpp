// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_STRINGIFIER
#define SSVS_UTILS_STRINGIFIER

#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Input/Combo.hpp"
#include "SSVStart/Input/Trigger.hpp"
#include "SSVStart/Utils/UtilsInput.hpp"

namespace ssvu
{
	template<typename TType> struct Stringifier<ssvs::Vec2<TType>>
	{
		using T = ssvs::Vec2<TType>;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "(";

			Internal::callStringifyImpl<TLogify, true>(mValue.x, mStream);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "; ";

			Internal::callStringifyImpl<TLogify, true>(mValue.y, mStream);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << ")";
		}
	};
	template<> struct Stringifier<sf::Color>
	{
		using T = sf::Color;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << "(";

			if(TLogify) mStream << Console::resetFmt() << Console::setColorFG(Console::Color::Red);
			mStream << int(mValue.r);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << ", ";

			if(TLogify) mStream << Console::resetFmt() << Console::setColorFG(Console::Color::Green);
			mStream << int(mValue.g);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << ", ";

			if(TLogify) mStream << Console::resetFmt() << Console::setColorFG(Console::Color::Blue);
			mStream << int(mValue.b);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << ", ";

			if(TLogify) mStream << Console::resetFmt() << Console::setColorFG(Console::Color::LightGray);
			mStream << int(mValue.a);

			if(TLogify) mStream << Console::setColorFG(Console::Color::LightGray) << Console::setStyle(Console::Style::Bold);
			mStream << ")";
		}
	};

	template<> struct Stringifier<ssvs::KKey>
	{
		using T = ssvs::KKey;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			if(TLogify) mStream << Console::setColorFG(Console::Color::Yellow);
			mStream << "(" + ssvs::getKeyName(mValue) + ")";
		}
	};

	template<> struct Stringifier<ssvs::MBtn>
	{
		using T = ssvs::MBtn;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			if(TLogify) mStream << Console::setColorFG(Console::Color::Green);
			mStream << "(" + ssvs::getBtnName(mValue) + ")";
		}
	};

	template<> struct Stringifier<ssvs::Input::Combo>
	{
		using T = ssvs::Input::Combo;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			mStream << "[";

			int added{0}, total{mValue.getKeys().count() + mValue.getBtns().count()};

			for(auto i(0u); i < mValue.getKeys().size(); ++i)
			{
				if(mValue.getKeys()[i])
				{
					++added;
					Internal::callStringifyImpl<TLogify, true>(ssvs::KKey(i - 1), mStream);
					mStream << ((added >= total) ? "" : ", ");
				}
			}

			for(auto i(0u); i < mValue.getBtns().size(); ++i)
			{
				if(mValue.getBtns()[i])
				{
					++added;
					Internal::callStringifyImpl<TLogify, true>(ssvs::MBtn(i - 1), mStream);
					mStream << ((added >= total) ? "" : ", ");
				}
			}

			mStream << "]";
		}
	};

	template<> struct Stringifier<ssvs::Input::Trigger>
	{
		using T = ssvs::Input::Trigger;
		template<bool TLogify> inline static void impl(const T& mValue, std::ostream& mStream)
		{
			mStream << "{";
			for(auto i(0u); i < mValue.getCombos().size(); ++i)
			{
				Internal::callStringifyImpl<TLogify, true>(mValue.getCombos()[i], mStream);
				mStream << ((i == mValue.getCombos().size() - 1) ? "" : ", ");
			}
			mStream << "}";
		}
	};
}

#endif
