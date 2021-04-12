// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include <SSVUtils/Json/Json.hpp>

#include <SFML/Network/Packet.hpp>

/// @brief Serialize ssvu JSON value into `sf::Packet`.
inline sf::Packet& operator<<(sf::Packet& mP, const ssvj::Val& mX)
{
    return mP << mX.getWriteToStr<ssvj::WSMinified>();
}

/// @brief Deserialize ssvu JSON value from `sf::Packet`.
inline sf::Packet& operator>>(sf::Packet& mP, ssvj::Val& mX)
{
    std::string str;
    mP >> str;
    mX.readFromStr(str);
    return mP;
}
