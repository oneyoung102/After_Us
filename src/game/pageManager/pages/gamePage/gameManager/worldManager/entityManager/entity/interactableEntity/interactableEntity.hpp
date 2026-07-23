#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class WindowManager;
class WorldManager;

class InteractableEntity : public Entity
{
    protected :
        bool __is_interacted;
    public :
        InteractableEntity(const tools::POSf& pos, float size = 1.f);
        virtual ~InteractableEntity() = default;

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;

        bool is_interacted() const;
        void set_interacted_state(bool state);

        virtual bool is_interactable_entity() const override {return true;}
};