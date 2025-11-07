#include "card.hpp"

#include <gtest/gtest.h>

//---------------------------------------------------------------------------------------------------------------------

TEST(CardTest, ValidStandardCardIsValid)
{
    Card card(Cards::Figure::Ace, Cards::Suit::Spades);
    EXPECT_TRUE(CardUtils::isValid(card));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardTest, ValidJokerCardIsValid)
{
    Card card(1);
    EXPECT_TRUE(CardUtils::isValid(card));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardTest, PartialInvalidCardIsInvalid)
{
    Card card(Cards::Figure::Ten, Cards::Suit::None);
    EXPECT_FALSE(CardUtils::isValid(card));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardTest, PartialInvalidJokerCardIsInvalid)
{
    Card card(Cards::Figure::Ten, Cards::Suit::None);
    card.jokerId = 1;
    EXPECT_FALSE(CardUtils::isValid(card));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardTest, JokerIsValid)
{
    Card card(1);
    EXPECT_TRUE(CardUtils::isValid(card));
    EXPECT_TRUE(CardUtils::isJoker(card));
}

//---------------------------------------------------------------------------------------------------------------------

TEST(CardTest, InvalidJokerIdIsInvalid)
{
    Card card(3);
    EXPECT_FALSE(CardUtils::isValid(card));
    EXPECT_FALSE(CardUtils::isJoker(card));
}
