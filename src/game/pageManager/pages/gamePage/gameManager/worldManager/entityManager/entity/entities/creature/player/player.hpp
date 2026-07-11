#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/pointer/pointer.hpp"
#include "tools/pos.hpp"

class WorldManager;

class Player : public Creature
{
    private:
        Pointer pointer;
    public:
        Player(const tools::POSf& pos);

        void set_reach(float reach);
        float get_reach() const;

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;

        const Pointer& get_pointer() const;
        
        virtual bool is_player() const override {return true;}
        
        virtual EntityName get_name() const override {return EntityName::player;}    
};