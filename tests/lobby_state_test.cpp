#include "server_components/lobby_state.hpp"

#include <optional>

#include <gtest/gtest.h>

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, InitialisedLobbyHasNoPlayers)
{
    LobbyState lobby;
    PlayerId player(std::string({"Jarek"}));
    EXPECT_FALSE(lobby.playerInLobby(player));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, InitialisedLobbyHasNoLobbyLeader)
{
    LobbyState lobby;
    EXPECT_EQ(lobby.getLobbyLeader(), std::nullopt);
}

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, AddedPlayerInLobby)
{
    LobbyState lobby;
    PlayerId player(std::string({"Jarek"}));
    lobby.registerPlayer(player);
    EXPECT_TRUE(lobby.playerInLobby(player));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, RemovedPlayerNoLongerInLobby)
{
    LobbyState lobby;
    PlayerId player(std::string({"Jarek"}));
    lobby.registerPlayer(player);
    lobby.removePlayer(player);
    EXPECT_FALSE(lobby.playerInLobby(player));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, FirstAddedPlayerIsLeader)
{
    LobbyState lobby;
    PlayerId player(std::string({"Jarek"}));
    lobby.registerPlayer(player);
    EXPECT_EQ(player, lobby.getLobbyLeader());
}

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, SecondAddedPlayerIsLeaderAfterFirstRemoval)
{
    LobbyState lobby;
    PlayerId player(std::string({"Jarek"}));
    PlayerId player2(std::string({"Benedict"}));
    lobby.registerPlayer(player);
    lobby.registerPlayer(player2);
    lobby.removePlayer(player);
    EXPECT_EQ(player2, lobby.getLobbyLeader());
}

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, AddingSamePlayerSecondTimeIsNullOp)
{
    LobbyState lobby;
    PlayerId player(std::string({"Jarek"}));
    lobby.registerPlayer(player);
    lobby.registerPlayer(player);
    EXPECT_EQ(lobby.getNumPlayers(), 1);
}

//---------------------------------------------------------------------------------------------------------------------

TEST(LobbyTest, RemovingSamePlayerSecondTimeIsNullOp)
{
    LobbyState lobby;
    PlayerId player(std::string({"Jarek"}));
    lobby.registerPlayer(player);
    lobby.removePlayer(player);
    lobby.removePlayer(player);
    EXPECT_EQ(lobby.getNumPlayers(), 0);
}
