#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "tools/pos.hpp"
#include <functional>

class WorldManager;
class World;

#define __HAND_ACTION_ARGUMENTS const tools::POSf& pointer_pos, const World& world, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer

class Player : public Creature
{
    private:
        static constexpr tools::POSf hitbox = {1, 0.5};
        static constexpr tools::POSf pointer_hitbox = {1, 2};

        using HAND_ACTION_TYPE = std::function<void(__HAND_ACTION_ARGUMENTS)>;
        HAND_ACTION_TYPE __main_hand_action, __off_hand_action;
        float reach;
    public:
        Player(const tools::POSf& pos = tools::POSf());

        void set_reach(float reach);
        float get_reach() const;

        virtual tools::POSf get_hitbox() const override;
        virtual tools::POSf get_pointer_hitbox() const override;

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;

        void interact(__HAND_ACTION_ARGUMENTS);
        void main_hand_action(__HAND_ACTION_ARGUMENTS);
        void off_hand_action(__HAND_ACTION_ARGUMENTS);
        
        
        virtual EntityName get_name() const override {return EntityName::player;}    

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Player, pos, size, entity_code, motion, ascendable_height, direction, max_health, health, power, time_for_attack, attack_distance, notice_distance, foot_state, reach);
};