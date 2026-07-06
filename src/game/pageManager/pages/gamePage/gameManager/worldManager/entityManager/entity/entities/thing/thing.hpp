#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity.hpp"

class Thing : public InteractableEntity
{
    public :
        Thing(const tools::POSf& pos, unsigned int size = 1);
        virtual ~Thing() = default;
};