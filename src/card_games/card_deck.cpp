#include "card_deck.hpp"

#include "enums/figure.hpp"
#include "enums/suit.hpp"

#include <random>

//---------------------------------------------------------------------------------------------------------------------

namespace
{
    int generateUniformInteger(const size_t a, const size_t b)
    {
        // Good old urandom
        static std::random_device rd("/dev/urandom");
        std::uniform_int_distribution<> uniform(a, b);
        return uniform(rd);
    }
}


//---------------------------------------------------------------------------------------------------------------------

bool CardDeck::operator==(const CardDeck & other) const
{
    if (cards.size() != other.cards.size())
    {
        return false;
    }
    return cards == other.cards;
}

//---------------------------------------------------------------------------------------------------------------------

void CardDeck::shuffle()
{
    // Fisher-Yates-Knuth
    for (auto i = cards.size() - 1; i > 0; i--)
    {
        const auto j = generateUniformInteger(0, i);
        const auto cardJ = cards[j];
        cards[j] = cards[i];
        cards[i] = cardJ;
    }
}

//---------------------------------------------------------------------------------------------------------------------

CardDeck CardDeckUtils::makeStandard52Deck()
{
    CardDeck deck;
    // TODO : Define these enum iterations with the enums.
    for (auto i = 1; i < 5; i++)
    {
        const Cards::Suit suit = static_cast<Cards::Suit>(i);
        for (auto j = 1; j < 14; j++)
        {
            const Cards::Figure figure = static_cast<Cards::Figure>(j);
            deck.addCard(Card(figure, suit));
        }
    }
    return deck;
}
