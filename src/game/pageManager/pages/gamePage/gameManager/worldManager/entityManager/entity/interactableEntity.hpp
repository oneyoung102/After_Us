#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class InteractableEntity : public Entity
{
    private :
    public :
        InteractableEntity(const tools::POSf& pos, unsigned int size = 1);
        virtual ~InteractableEntity() = default;
};