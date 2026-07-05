#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/thingManager/thing/thing.hpp"

class InteractableThing : public Thing
{
    private :
    public :
        InteractableThing(const tools::POSf& pos, unsigned int size = 1);
        virtual ~InteractableThing() = default;
};