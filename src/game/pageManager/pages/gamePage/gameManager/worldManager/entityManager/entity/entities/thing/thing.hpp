#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class Thing : public Entity
{
    public :
        Thing(const tools::POSf& pos, float size = 1.f);
        virtual ~Thing() = default;
        
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}
        virtual bool is_thing() const override {return true;}
};