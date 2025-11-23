#include "blackjack.hpp"

#include <cmath>
#include <iterator>
#include <utility>

//---------------------------------------------------------------------------------------------------------------------

void BlackJackGame::initialSetup(uint8_t numPlayers)
{
    if (!canPlayWith(numPlayers))
    {
        return;
    }

    deck = CardDeckUtils::makeStandard52Deck();
    deck.shuffle();

    // Hand out cards to players
    for (uint8_t i = 0; i < numPlayers; i++)
    {
        hands[i].addCard(deck.drawCard().value());
    }

    topCard = deck.drawCard().value();

    for (std::uint8_t player = 0; player < numPlayers; player++)
    {
        playerQueue.push_back(player);
    }
}

//---------------------------------------------------------------------------------------------------------------------

bool BlackJackGame::playMove(const Card & card)
{
    if (!isLegitimateMove(card))
    {
        return false;
    }

    // Special Card Effects
    // Ace - Can now change suit -> How do I report this back to via WS?
    // King - Order reversed if ended on/skips turn in a 1v1.
    // Queen - Next card can be any figure of the same suit. X
    // Black Jack - +5 for next player, if END turn on it. X
    // Red Jack - Nullify current black jack pile. X
    // 8 - Skips next player's turn.
    // 2 - Pick up two for next player, if END turn on it.

    forcedSuit = std::nullopt;
    forcedFigure = std::nullopt;

    switch (card.figure)
    {
        case Cards::Figure::Ace:
        {
            if (!prevCard)
            {
                canChangeSuit = true;
                if (card.suit != topCard.suit)
                {
                    forcedToChangeSuit = true;
                }
            }
            else if (prevCard->figure == Cards::Figure::Two)
            {
                stackedCards = 0;
            }
            break;
        }
        case Cards::Figure::King:
        {
            kingsInSeries += 1;
            break;
        }
        case Cards::Figure::Jack:
        {
            if (Cards::isBlack(topCard.suit))
            {
                stackedCards += 5;
            }
            else if ((Cards::isRed(topCard.suit))
                    && (topCard.figure == Cards::Figure::Jack)
                    && (Cards::isBlack(topCard.suit)))
            {
                stackedCards = 0;
            }
            break;
        }
        case Cards::Figure::Queen:
        case Cards::Figure::Ten:
        case Cards::Figure::Three:
        {
            stackedCards = 0;
            break;
        }
        case Cards::Figure::Two:
        {
            stackedCards += 2;
            break;
        }
        case Cards::Figure::None:
        {
            // Don't allow this enum to somehow get in game.
            return false;
        }
        default:
        {
            break;
        }
    }

    if (!(card.figure == Cards::Figure::King))
    {
        kingsInSeries = 0;
    }

    prevCard = card;
    deck.addCard(topCard);
    topCard = card;
    hasPlayedOrPickedUp = true;
    return true;
}

//---------------------------------------------------------------------------------------------------------------------

void BlackJackGame::chooseSuit(const Cards::Suit suit)
{
    forcedSuit = suit;
    forcedToChangeSuit = false;
    canChangeSuit = false;
}

//---------------------------------------------------------------------------------------------------------------------

void BlackJackGame::pickup()
{
    if (stackedCards)
    {
        forcedFigure = std::nullopt;
        for (std::uint8_t card = 0; card < stackedCards; card++)
        {
            hands[currentPlayer].addCard(getPileCard());
        }
        stackedCards = 0;
    }
    hasPlayedOrPickedUp = true;
}

//---------------------------------------------------------------------------------------------------------------------

Card BlackJackGame::getPileCard()
{
    if (deck.isEmpty())
    {
        reshuffle();
    }
    return deck.drawCard().value();
}

//---------------------------------------------------------------------------------------------------------------------

void BlackJackGame::reshuffle()
{
    std::swap(deck, playedPile);
    deck.shuffle();
}

//---------------------------------------------------------------------------------------------------------------------

void BlackJackGame::endTurn()
{
    if (!hasPlayedOrPickedUp)
    {
        // Can't end turn without one of these.
        return;
    }

    if (forcedToChangeSuit && !forcedSuit)
    {
        // Can't end turn if you haven't changed suit yet.
        return;
    }

    const auto currentIndex = nextPlayerIndex;
    if (prevCard)
    {
        // Played, check if end card has any special effects.
        handleEndCard(prevCard.value());
    }

    nextPlayerIndex = (nextPlayerIndex + direction) % numPlayers;
    if (hands[currentPlayer].isEmpty())
    {
        // Need to remove the player and heal the index.
        playerQueue.erase(std::next(playerQueue.begin(),currentIndex));
        // The next index was incremented once too many now that we have removed
        // a player, if we were moving forwards in players.
        if (direction == 1)
        {
            nextPlayerIndex = (nextPlayerIndex - 1) % numPlayers;
        }
        numPlayers -= 1;
    }
}

//---------------------------------------------------------------------------------------------------------------------

void BlackJackGame::handleEndCard(const Card & card)
{
    switch (card.figure)
    {
        case Cards::Figure::King:
        {
            if (numPlayers == 2)
            {
                nextPlayerIndex = (nextPlayerIndex + direction) % 2;
            }
            else
            {
                direction = std::pow(-1, kingsInSeries);
            }
            kingsInSeries = 0;
            break;
        }
        case Cards::Figure::Queen:
        {
            // Can't end turn on Queen, must pick-up a card
            pickup();
            break;
        }
        case Cards::Figure::Jack:
        {
            if (Cards::isBlack(prevCard->suit))
            {
                forcedFigure = Cards::Figure::Jack;
            }
            break;
        }
        case Cards::Figure::Eight:
        {
            nextPlayerIndex = (nextPlayerIndex + direction) % numPlayers;
            break;
        }
        case Cards::Figure::Two:
        {
            forcedFigure = Cards::Figure::Two;
            break;
        }
        default:
        {
            break;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

void BlackJackGame::advanceToNextPlayer()
{
    prevCard = std::nullopt;
    hasPlayedOrPickedUp = false;
    currentPlayer = playerQueue[nextPlayerIndex];
}

//---------------------------------------------------------------------------------------------------------------------

bool BlackJackGame::isLegitimateMove(const Card & card) const
{
    if (!prevCard)
    {
        return isLegitimateFirstMove(card);
    }
    else if (prevCard->figure == Cards::Figure::Queen)
    {
        return isLegitimateOnQueenMove(card);
    }
    else
    {
        return isLegitimateMoveInSeries(card);
    }
}

//---------------------------------------------------------------------------------------------------------------------

bool BlackJackGame::isLegitimateFirstMove(const Card & card) const
{
    if (forcedFigure)
    {
        return (card.figure == forcedFigure);
    }

    if (topCard.figure == card.figure)
    {
        return true;
    }

    const auto matchSuit = forcedSuit.value_or(topCard.suit);
    if (card.suit == matchSuit)
    {
        return true;
    }

    return (card.figure == Cards::Figure::Ace);
}

//---------------------------------------------------------------------------------------------------------------------

bool BlackJackGame::isLegitimateOnQueenMove(const Card & card) const
{
    return ((card.figure == Cards::Figure::Queen)|| (prevCard->suit == card.suit));
}

//---------------------------------------------------------------------------------------------------------------------

bool BlackJackGame::isLegitimateMoveInSeries(const Card & card) const
{
    if (forcedToChangeSuit || forcedSuit)
    {
        return false;
    }

    if (prevCard->figure == card.figure)
    {
        return true;
    }

    return ((prevCard->suit == card.suit) && BlackJackUtils::inSeries(prevCard->figure, card.figure));
}

//---------------------------------------------------------------------------------------------------------------------

bool BlackJackUtils::inSeries(Cards::Figure prev, Cards::Figure next)
{
    if (prev == Cards::Figure::Ace)
    {
        return ((next == Cards::Figure::King) || (next == Cards::Figure::Two));
    }

    if (prev == Cards::Figure::King)
    {
        return ((next == Cards::Figure::Ace) || (next == Cards::Figure::Queen));
    }

    int difference = Cards::figureToInt(next) - Cards::figureToInt(prev);
    return ((difference == 1) || (difference == -1));
}
