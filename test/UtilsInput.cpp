// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "./utils/test_utils.hpp"
#include <SSVStart/SSVStart.hpp>

int main()
{
    TEST_ASSERT_NS(ssvs::isKKeyNameValid("kUp"));
    TEST_ASSERT_NS(ssvs::isKKeyNameValid("kA"));
    TEST_ASSERT_NS(ssvs::isKKeyNameValid("kB"));
    TEST_ASSERT_NS(ssvs::isKKeyNameValid("kNum0"));
    TEST_ASSERT_NS(ssvs::isKKeyNameValid("kF1"));
    TEST_ASSERT_NS(!ssvs::isKKeyNameValid(""));
    TEST_ASSERT_NS(!ssvs::isKKeyNameValid("Up"));
    TEST_ASSERT_NS(!ssvs::isKKeyNameValid("kup"));
    TEST_ASSERT_NS(!ssvs::isKKeyNameValid("F1"));
    TEST_ASSERT_NS(!ssvs::isKKeyNameValid("kf1"));

    TEST_ASSERT_NS(ssvs::isMBtnNameValid("bLeft"));
    TEST_ASSERT_NS(ssvs::isMBtnNameValid("bExtra1"));
    TEST_ASSERT_NS(!ssvs::isMBtnNameValid(""));
    TEST_ASSERT_NS(!ssvs::isMBtnNameValid("Left"));
    TEST_ASSERT_NS(!ssvs::isMBtnNameValid("Extra1"));
    TEST_ASSERT_NS(!ssvs::isMBtnNameValid("bleft"));

    TEST_ASSERT_NS(ssvs::getKKey("kUp") == ssvs::KKey::Up);
    TEST_ASSERT_NS(ssvs::getKKey("kA") == ssvs::KKey::A);
    TEST_ASSERT_NS(ssvs::getKKey("kB") == ssvs::KKey::B);
    TEST_ASSERT_NS(ssvs::getKKey("kNum0") == ssvs::KKey::Num0);
    TEST_ASSERT_NS(ssvs::getKKey("kF1") == ssvs::KKey::F1);

    TEST_ASSERT_NS(ssvs::getMBtn("bLeft") == ssvs::MBtn::Left);
    TEST_ASSERT_NS(ssvs::getMBtn("bExtra1") == ssvs::MBtn::Extra1);

    TEST_ASSERT_NS(ssvs::getKKeyName(ssvs::KKey::Up) == "kUp");
    TEST_ASSERT_NS(ssvs::getKKeyName(ssvs::KKey::A) == "kA");
    TEST_ASSERT_NS(ssvs::getKKeyName(ssvs::KKey::B) == "kB");
    TEST_ASSERT_NS(ssvs::getKKeyName(ssvs::KKey::Num0) == "kNum0");
    TEST_ASSERT_NS(ssvs::getKKeyName(ssvs::KKey::F1) == "kF1");

    TEST_ASSERT_NS(ssvs::getMBtnName(ssvs::MBtn::Left) == "bLeft");
    TEST_ASSERT_NS(ssvs::getMBtnName(ssvs::MBtn::Extra1) == "bExtra1");
}
