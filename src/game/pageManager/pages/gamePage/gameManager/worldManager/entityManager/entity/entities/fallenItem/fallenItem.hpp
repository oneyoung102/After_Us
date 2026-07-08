#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity.hpp"

class FallenItem : public InteractableEntity
{
    public :
        FallenItem(const tools::POSf& pos);
        virtual ~FallenItem() = default;
        virtual bool is_fallen_item() const override {return true;}
        
};