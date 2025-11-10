#pragma once

#include "card.hpp"

#include <vector>

//---------------------------------------------------------------------------------------------------------------------

class CardDeck
{
public:
    CardDeck() {}
    CardDeck(std::vector<Card> deck) : cards(deck) {}

    bool operator==(const CardDeck & other) const;

    void addCard(Card card) { cards.push_back(card); }
    Card at(std::size_t i) const { return cards[i]; }
    const std::vector<Card> & viewCards() const { return cards; }

    bool isEmpty() { return cards.size() == 0; }
    void shuffle();

private:
    std::vector<Card> cards = {};
};

//---------------------------------------------------------------------------------------------------------------------

namespace CardDeckUtils
{
    CardDeck makeStandard52Deck();
}
