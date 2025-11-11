#include "lobby_state.hpp"

#include <algorithm>

//---------------------------------------------------------------------------------------------------------------------

bool LobbyState::playerInLobby(const PlayerId & player) const
{
    return std::find(players.begin(), players.end(), player) != players.end();
}

//---------------------------------------------------------------------------------------------------------------------

void LobbyState::registerPlayer(const PlayerId & player)
{
    // TODO : Do not silently catch this. I'll want this in some form of server logs.
    if (playerInLobby(player))
    {
        return;
    }

    players.push_back(player);

    if (!lobbyLeader)
    {
        lobbyLeader = player;
    }
}

//---------------------------------------------------------------------------------------------------------------------

void LobbyState::removePlayer(const PlayerId & player)
{
    // TODO : Do not silently catch this. I'll want this in some form of server logs.
    if (!playerInLobby(player))
    {
        return;
    }

    auto playerAt = std::find(players.begin(), players.end(), player);
    players.erase(playerAt);

    // Make it work with const ffs
    if (player == lobbyLeader.value())
    {
        lobbyLeader = players.size() ? std::make_optional<PlayerId>(players[0]) : std::nullopt;
    }
}

