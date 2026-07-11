#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class WindowManager;
class WorldManager;

class InteractableEntity : public Entity
{
    private :
    public :
        InteractableEntity(const tools::POSf& pos, unsigned int size = 1);
        virtual ~InteractableEntity() = default;

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;

        virtual bool is_interactable_entity() const override {return true;}
};