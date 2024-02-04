// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "./utils/test_utils.hpp"
#include <SSVStart/SSVStart.hpp>

int main()
{
    using namespace std;
    using namespace ssvu;
    using namespace ssvj;
    using namespace ssvs;

#define EXECTEST                                                \
    do                                                          \
    {                                                           \
        auto s(Val{original}.getWriteToStr());                  \
        TEST_ASSERT_NS_OP(fromStr(s).as<Type>(), ==, original); \
    } while(false)

#define MAKETEST(T, ...)            \
    do                              \
    {                               \
        using Type = T;             \
        Type original(__VA_ARGS__); \
        EXECTEST;                   \
    } while(false)

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
    MAKETEST(ssvs::MBtn, ssvs::MBtn::Extra1);

    MAKETEST(ssvs::Input::Combo, {ssvs::KKey::Up}, {ssvs::MBtn::Left});
    MAKETEST(ssvs::Input::Trigger,
        {{{ssvs::KKey::Up}, {ssvs::MBtn::Left}}, {ssvs::KKey::F1}});

#undef EXECTEST
#undef MAKETEST
}
