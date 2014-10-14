// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TESTS
#define SSVS_TESTS

#include <SSVUtils/Test/Test.hpp>

SSVUT_TEST(SSVS_UtilsInputTests)
{
	SSVUT_EXPECT(ssvs::isKKeyNameValid("kUp"));
	SSVUT_EXPECT(ssvs::isKKeyNameValid("kA"));
	SSVUT_EXPECT(ssvs::isKKeyNameValid("kB"));
	SSVUT_EXPECT(ssvs::isKKeyNameValid("kNum0"));
	SSVUT_EXPECT(ssvs::isKKeyNameValid("kF1"));
	SSVUT_EXPECT(!ssvs::isKKeyNameValid(""));
	SSVUT_EXPECT(!ssvs::isKKeyNameValid("Up"));
	SSVUT_EXPECT(!ssvs::isKKeyNameValid("kup"));
	SSVUT_EXPECT(!ssvs::isKKeyNameValid("F1"));
	SSVUT_EXPECT(!ssvs::isKKeyNameValid("kf1"));

	SSVUT_EXPECT(ssvs::isMBtnNameValid("bLeft"));
	SSVUT_EXPECT(ssvs::isMBtnNameValid("bXButton1"));
	SSVUT_EXPECT(!ssvs::isMBtnNameValid(""));
	SSVUT_EXPECT(!ssvs::isMBtnNameValid("Left"));
	SSVUT_EXPECT(!ssvs::isMBtnNameValid("XButton1"));
	SSVUT_EXPECT(!ssvs::isMBtnNameValid("bleft"));

	SSVUT_EXPECT(ssvs::getKKey("kUp") == ssvs::KKey::Up);
	SSVUT_EXPECT(ssvs::getKKey("kA") == ssvs::KKey::A);
	SSVUT_EXPECT(ssvs::getKKey("kB") == ssvs::KKey::B);
	SSVUT_EXPECT(ssvs::getKKey("kNum0") == ssvs::KKey::Num0);
	SSVUT_EXPECT(ssvs::getKKey("kF1") == ssvs::KKey::F1);

	SSVUT_EXPECT(ssvs::getMBtn("bLeft") == ssvs::MBtn::Left);
	SSVUT_EXPECT(ssvs::getMBtn("bXButton1") == ssvs::MBtn::XButton1);

	SSVUT_EXPECT(ssvs::getKKeyName(ssvs::KKey::Up) == "kUp");
	SSVUT_EXPECT(ssvs::getKKeyName(ssvs::KKey::A) == "kA");
	SSVUT_EXPECT(ssvs::getKKeyName(ssvs::KKey::B) == "kB");
	SSVUT_EXPECT(ssvs::getKKeyName(ssvs::KKey::Num0) == "kNum0");
	SSVUT_EXPECT(ssvs::getKKeyName(ssvs::KKey::F1) == "kF1");

	SSVUT_EXPECT(ssvs::getMBtnName(ssvs::MBtn::Left) == "bLeft");
	SSVUT_EXPECT(ssvs::getMBtnName(ssvs::MBtn::XButton1) == "bXButton1");
}

SSVUT_TEST(SSVS_UtilsJsonNewTests)
{
	using namespace std;
	using namespace ssvu;
	using namespace ssvj;
	using namespace ssvs;

	#define EXECTEST \
		do \
		{ \
			auto s(Val{original}.getWriteToStr()); \
			SSVUT_EXPECT(Val::fromStr(s).as<Type>() == original); \
		} while(false)

	#define MAKETEST(T, ...)	do { using Type = T; Type original(__VA_ARGS__); EXECTEST; } while(false)

	MAKETEST(ssvs::Vec2f, 52.f, 33.f);
	MAKETEST(ssvs::Vec2i, 52, -33);
	MAKETEST(ssvs::Vec2u, 52, 33);

	MAKETEST(sf::Color, 52, 33, 22);
	MAKETEST(sf::Color, 0, 0, 0);
	MAKETEST(sf::Color, 255, 255, 255);

	MAKETEST(ssvs::KKey, ssvs::KKey::Up);
	MAKETEST(ssvs::KKey, ssvs::KKey::A);
	MAKETEST(ssvs::KKey, ssvs::KKey::B);
	MAKETEST(ssvs::KKey, ssvs::KKey::Num0);
	MAKETEST(ssvs::KKey, ssvs::KKey::F1);

	MAKETEST(ssvs::MBtn, ssvs::MBtn::Left);
	MAKETEST(ssvs::MBtn, ssvs::MBtn::XButton1);

	MAKETEST(ssvs::Input::Combo, {ssvs::KKey::Up}, {ssvs::MBtn::Left});
	MAKETEST(ssvs::Input::Trigger, {{{ssvs::KKey::Up}, {ssvs::MBtn::Left}}, {ssvs::KKey::F1}});

	#undef EXECTEST
	#undef MAKETEST
}

#endif
