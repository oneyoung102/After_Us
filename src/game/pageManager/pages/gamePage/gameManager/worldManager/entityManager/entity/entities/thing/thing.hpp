#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class Thing : public Entity
{
    public :
        enum class ThingName
        {
            tree,
            COUNT
        };
        
    private :
        const ThingName thing_name;

    public :
        Thing(const tools::POSf& pos, float size = 1.f, ThingName thing_name = ThingName::tree);
        virtual ~Thing() = default;

        ThingName get_thing_name() const;
        
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}
        virtual bool is_thing() const override {return true;}
};