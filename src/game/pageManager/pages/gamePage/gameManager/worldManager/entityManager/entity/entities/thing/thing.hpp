#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class Thing : public Entity
{
    public :
        Thing(const tools::POSf& pos = tools::POSf(), float size = 1.f);
        virtual ~Thing() = default;
        
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}
        virtual bool is_thing() const override {return true;}

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Thing, pos, size, entity_code);
};