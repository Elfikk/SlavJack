#pragma once

#include "enums/figure.hpp"
#include "enums/jokers.hpp"
#include "enums/suit.hpp"

//---------------------------------------------------------------------------------------------------------------------

struct Card
{
    Card(Cards::Figure _figure, Cards::Suit _suit) : suit(_suit), figure(_figure) {}
    Card(Cards::JokerType id) : jokerId(id) {}

    Cards::Suit suit = Cards::Suit::None;
    Cards::Figure figure = Cards::Figure::None;
    Cards::JokerType jokerId = Cards::JokerType::None;
};

//---------------------------------------------------------------------------------------------------------------------

namespace CardUtils
{
    bool isStandardCard(const Card & card)
    {
        return ((card.suit != Cards::Suit::None)
             && (card.figure != Cards::Figure::None)
             && (card.jokerId == Cards::JokerType::None));
    }

//---------------------------------------------------------------------------------------------------------------------

    bool isJoker(const Card & card)
    {
        return ((card.jokerId == Cards::JokerType::Red || card.jokerId == Cards::JokerType::Black) &&
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
