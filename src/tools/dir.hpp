#pragma once

#include "tools/pos.hpp"
#include <array>

namespace tools
{
    enum Direction : size_t
    {
        DOWN = 0,
        UP = 1,
        RIGHT = 2,
        LEFT = 3
    };
    inline constexpr Direction operator~(Direction d)
    {
        return static_cast<Direction>(static_cast<size_t>(d) ^ 1);
    }
    inline constexpr const std::array<POSi, 4> DIR = {POSi(0, 1), POSi(0, -1), POSi(1, 0), POSi(-1, 0)};
}
