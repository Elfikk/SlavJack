#pragma once

#include "card_games/card.hpp"
#include "card_games/card_deck.hpp"

#include "card_games/enums/suit.hpp"

#include <cstdint>
#include <map>

//---------------------------------------------------------------------------------------------------------------------

class BlackJackGame
{

public:
    BlackJackGame() {}

    // Max 7 players, cannot hand out starting hands otherwise.
    bool canPlayWith(std::uint8_t numPlayers) const { return ((numPlayers > 1) && (numPlayers < 8)); };
    void initialSetup(std::uint8_t numPlayers);

    bool isLegitimateMove(const Card &) const;
    bool playMove(const Card &);
    void chooseSuit(const Cards::Suit);

    Card getTopCard() const { return topCard; }

    // This should be only accessible in testing...
    void setMockTopCard(const Card & card) { topCard = card; }

    // note: picking up from the pile takes at least one card, but can take more
    // if twos/blackjacks are involved
    void pickup();
    void endTurn();
    void advanceToNextPlayer();

    bool gameEnded() { return (numPlayers == 1); }

private:
    bool isLegitimateFirstMove(const Card &) const;
    bool isLegitimateMoveInSeries(const Card &) const;
    bool isLegitimateOnQueenMove(const Card &) const;

    void handleEndCard(const Card &);

    Card getPileCard();
    void reshuffle();

    CardDeck deck;

    CardDeck playedPile;
    Card topCard = Card(Cards::JokerType::None);

    std::optional<Card> prevCard;
    // note: in case an Ace played. we do not want to change the Ace's suit
    // directly as we would shuffle the wrong suit back into the deck...
    std::optional<Cards::Suit> forcedSuit;

    // note: in case a Two or Black Jack has turn ended on, we have to force
    // the next player's figure to be the same.
    std::optional<Cards::Figure> forcedFigure;

    // In case an Ace is played on the previous turn when it could not be
    // played directly, a player is forced to change suit and end their turn.
    bool forcedToChangeSuit = false;
    bool canChangeSuit = false;
    bool hasChangedSuit = false;

    bool hasPlayedOrPickedUp = false;

    std::uint8_t kingsInSeries = 0;

    // Number of cards currently stacked to be picked up by another player
    std::uint8_t stackedCards = 0;

    std::uint8_t numPlayers;
    std::uint8_t currentPlayer = 0;
    std::int8_t nextPlayerIndex = 0;
    int direction = 1;
    std::vector<std::uint8_t> playerQueue = {};
    std::map<uint8_t, CardDeck> hands;
};

//---------------------------------------------------------------------------------------------------------------------

namespace BlackJackUtils
{
    bool inSeries(Cards::Figure prev, Cards::Figure next);
};
