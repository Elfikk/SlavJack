#include "card_games/blackjack.hpp"

#include <cstdint>

#include <gtest/gtest.h>

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CanSetup)
{
    BlackJackGame game;
    game.initialSetup(2);
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CanPlayAceFirst)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::Eight, Cards::Suit::Spades));
    EXPECT_TRUE(game.isLegitimateMove(Card(Cards::Figure::Ace, Cards::Suit::Spades)));
    EXPECT_TRUE(game.isLegitimateMove(Card(Cards::Figure::Ace, Cards::Suit::Hearts)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CanPlaySameSuitFirst)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    EXPECT_TRUE(game.isLegitimateMove(Card(Cards::Figure::Two, Cards::Suit::Spades)));
    EXPECT_FALSE(game.isLegitimateMove(Card(Cards::Figure::Two, Cards::Suit::Hearts)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CanPlaySameFigureFirst)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    EXPECT_TRUE(game.isLegitimateMove(Card(Cards::Figure::King, Cards::Suit::Spades)));
    EXPECT_FALSE(game.isLegitimateMove(Card(Cards::Figure::Queen, Cards::Suit::Hearts)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CanPlayAnyFigureSameSuitOnQueen)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    EXPECT_TRUE(game.playMove(Card(Cards::Figure::Queen, Cards::Suit::Spades)));
    EXPECT_TRUE(game.isLegitimateMove(Card(Cards::Figure::Five, Cards::Suit::Spades)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CanPlayQueenOnQueen)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    EXPECT_TRUE(game.playMove(Card(Cards::Figure::Queen, Cards::Suit::Spades)));
    EXPECT_TRUE(game.isLegitimateMove(Card(Cards::Figure::Queen, Cards::Suit::Hearts)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CanPlaySeriesCards)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    EXPECT_TRUE(game.playMove(Card(Cards::Figure::Nine, Cards::Suit::Spades)));
    EXPECT_TRUE(game.isLegitimateMove(Card(Cards::Figure::Eight, Cards::Suit::Spades)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CannotPlaySeriesCardsIfDifferentSuit)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    EXPECT_TRUE(game.playMove(Card(Cards::Figure::Nine, Cards::Suit::Spades)));
    EXPECT_FALSE(game.isLegitimateMove(Card(Cards::Figure::Eight, Cards::Suit::Hearts)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CannotPlayNonTwoOnStackTwo)
{
    BlackJackGame game;
    game.initialSetup(2);
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    game.playMove(Card(Cards::Figure::Two, Cards::Suit::Spades));
    game.endTurn();
    game.advanceToNextPlayer();
    EXPECT_FALSE(game.isLegitimateMove(Card(Cards::Figure::Three, Cards::Suit::Spades)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CannotPlayNonJackCardOnStackBlackJack)
{
    BlackJackGame game;
    game.initialSetup(2);
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    game.playMove(Card(Cards::Figure::Jack, Cards::Suit::Spades));
    game.endTurn();
    EXPECT_FALSE(game.isLegitimateMove(Card(Cards::Figure::Three, Cards::Suit::Spades)));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(BlackJack, CannotPlayCardOnWildcardAce)
{
    BlackJackGame game;
    game.setMockTopCard(Card(Cards::Figure::King, Cards::Suit::Spades));
    game.playMove(Card(Cards::Figure::Ace, Cards::Suit::Hearts));
    EXPECT_FALSE(game.isLegitimateMove(Card(Cards::Figure::King, Cards::Suit::Hearts)));
}
