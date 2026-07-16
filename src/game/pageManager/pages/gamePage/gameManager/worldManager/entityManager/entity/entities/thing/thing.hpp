#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity/interactableEntity.hpp"

class Thing : public InteractableEntity
{
    public :
        Thing(const tools::POSf& pos, tools::POSf size = {1.f, 1.f});
        virtual ~Thing() = default;
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}
};