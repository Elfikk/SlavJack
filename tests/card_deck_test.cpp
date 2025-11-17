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

//---------------------------------------------------------------------------------------------------------------------

TEST(CardDeckTest, DrawingFromEmptyDeckNullOpts)
{
    CardDeck deck;
    EXPECT_TRUE(deck.isEmpty()); // In case default constructor changed...
    EXPECT_EQ(deck.drawCard(), std::nullopt);
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardDeckTest, DrawingReturnsTopCard)
{
    CardDeck deck;
    std::vector<Card> cards(
        {
            Card(Cards::Figure::King, Cards::Suit::Spades),
            Card(Cards::Figure::Queen, Cards::Suit::Diamonds),
            Card(Cards::Figure::Jack, Cards::Suit::Hearts),
            Card(Cards::Figure::Ace, Cards::Suit::Clubs)
        });

    for (size_t i = 0; i < cards.size(); i++)
    {
        deck.addCard(cards[i]);
    }

    for (size_t j = cards.size() - 1; j > -1; j--)
    {
        EXPECT_EQ(deck.drawCard(), cards[j]);
    }
}
