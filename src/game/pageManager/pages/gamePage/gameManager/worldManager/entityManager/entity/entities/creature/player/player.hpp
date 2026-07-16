#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "tools/pos.hpp"
#include <functional>

class WorldManager;

class Player : public Creature
{
    private:
        using HAND_ACTION_TYPE = std::function<void(const tools::POSf&, const std::function<std::vector<std::shared_ptr<Entity>>()>&)>;
        HAND_ACTION_TYPE __main_hand_action, __off_hand_action;
        float reach;
    public:
        Player(const tools::POSf& pos);

        void set_reach(float reach);
        float get_reach() const;

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;

        void main_hand_action(const tools::POSf& pointer_pos, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer);
        void off_hand_action(const tools::POSf& pointer_pos, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer);
        
        virtual bool is_player() const override {return true;}
        
        virtual EntityName get_name() const override {return EntityName::player;}    
};