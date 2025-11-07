#pragma once

#include "enums/figure.hpp"
#include "enums/suit.hpp"

//---------------------------------------------------------------------------------------------------------------------

struct Card
{
    Card(Cards::Figure _figure, Cards::Suit _suit) : suit(_suit), figure(_figure) {}
    Card(unsigned int id) : suit(Cards::Suit::None), figure(Cards::Figure::None), jokerId(id) {}

    Cards::Suit suit;
    Cards::Figure figure;
    // Note: JokerId is 1 for Red, 2 for Black
    unsigned int jokerId = 0;
};

//---------------------------------------------------------------------------------------------------------------------

namespace CardUtils
{
    bool isStandardCard(const Card & card)
    {
        return ((card.suit != Cards::Suit::None) && (card.figure != Cards::Figure::None) && (card.jokerId == 0));
    }

//---------------------------------------------------------------------------------------------------------------------

    bool isJoker(const Card & card)
    {
        return ((card.jokerId == 1 || card.jokerId == 2) &&
        (card.suit == Cards::Suit::None) && (card.figure == Cards::Figure::None));
    }

//---------------------------------------------------------------------------------------------------------------------

    bool isValid(const Card & card)
    {
        return (isStandardCard(card) || isJoker(card));
    }

//---------------------------------------------------------------------------------------------------------------------

    bool isFaceCard(const Card & card)
    {
        return ((card.figure == Cards::Figure::King)
            || (card.figure == Cards::Figure::Queen)
            || (card.figure == Cards::Figure::Jack));
    }
}
