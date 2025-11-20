#pragma once

#include <limits>

namespace Cards
{
    enum class Figure
    {
        Ace = 1,
        King = 13,
        Queen = 12,
        Jack = 11,
        Ten = 10,
        Nine = 9,
        Eight = 8,
        Seven = 7,
        Six = 6,
        Five = 5,
        Four = 4,
        Three = 3,
        Two = 2,
        None = std::numeric_limits<int>::max()
    };

    inline int figureToInt(Figure figure)
    {
        return static_cast<int>(figure);
    }

    inline Figure toFigure(int value)
    {
        return static_cast<Figure>(value);
    }
}
