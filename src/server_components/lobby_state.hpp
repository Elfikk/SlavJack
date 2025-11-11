#pragma once

#include <optional>
#include <string>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------

struct PlayerId
{
    PlayerId(const std::string & playerName) : name(playerName) {}

    bool operator==(const PlayerId & player) const { return name == player.name; }

    std::string name;
};

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
