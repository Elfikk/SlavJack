#include "card_games/card_deck.hpp"

#include <vector>

#include <gtest/gtest.h>

//---------------------------------------------------------------------------------------------------------------------

TEST(CardDeckTest, EmptyInitDeckIsEmpty)
{
    CardDeck deck;
    EXPECT_TRUE(deck.isEmpty());
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardDeckTest, EmptyInitDecksAreEqual)
{
    CardDeck deck;
    CardDeck deck2;
    EXPECT_TRUE(deck == deck2);
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardDeckTest, ShuffleChangesOrder)
{
    auto deck = CardDeckUtils::makeStandard52Deck();
    const auto cardsBeforeShuffle = deck.viewCards();
    deck.shuffle();
    EXPECT_FALSE(cardsBeforeShuffle == deck.viewCards()); // Chance of Failure is 1 / 52!
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardDeckTest, Standard52DecksSameOrder)
{
    auto deck = CardDeckUtils::makeStandard52Deck();
    auto deck2 = CardDeckUtils::makeStandard52Deck();
    EXPECT_TRUE(deck == deck2);
}
