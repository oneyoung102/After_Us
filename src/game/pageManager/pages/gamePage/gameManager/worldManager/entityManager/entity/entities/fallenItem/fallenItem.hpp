#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity/interactableEntity.hpp"

class FallenItem : public InteractableEntity
{
    public :
        FallenItem(const tools::POSf& pos);
        virtual ~FallenItem() = default;
        virtual bool is_fallen_item() const override {return true;}
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}
};