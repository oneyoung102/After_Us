#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "tools/pos.hpp"

class Player : public Creature
{
    private:

    public:
        Player(const tools::POSf& pos);

        virtual bool is_player() const override {return true;}
        
    virtual EntityName get_name() const override {return EntityName::player;}    
};