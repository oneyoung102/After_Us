#pragma once

#include "game/pages/gamePage/gameManager/thing/thing.hpp"

class InteractableThing : public Thing
{
    private :
    public :
        InteractableThing(const tools::POSf& pos, unsigned int size = 1);
        virtual ~InteractableThing() = default;
};