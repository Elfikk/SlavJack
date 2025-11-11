#pragma once

#include "server_components/player_id.hpp"

#include <optional>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------

class LobbyState
{
public:
    LobbyState() {}

    bool playerInLobby(const PlayerId &) const;

    void registerPlayer(const PlayerId &);
    void removePlayer(const PlayerId &);

    std::optional<PlayerId> getLobbyLeader() { return lobbyLeader; }
    std::size_t getNumPlayers() { return players.size(); }

private:
    std::vector<PlayerId> players = {};
    std::optional<PlayerId> lobbyLeader = std::nullopt;
};
