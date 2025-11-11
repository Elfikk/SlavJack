#pragma once

#include <string>

//---------------------------------------------------------------------------------------------------------------------

struct PlayerId
{
    PlayerId(const std::string & playerName) : name(playerName) {}

    bool operator==(const PlayerId & player) const { return name == player.name; }

    std::string name;
};
