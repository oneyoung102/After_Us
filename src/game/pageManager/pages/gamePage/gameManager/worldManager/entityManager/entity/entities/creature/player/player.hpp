#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "tools/pos.hpp"
#include <functional>

class WorldManager;
class World;

#define __HAND_ACTION_ARGUMENTS const tools::POSf& pointer_pos, const World& world, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer
#define __CAST_HAND_ACTION(func) [this](__HAND_ACTION_ARGUMENTS){return func(pointer_pos, world, find_collided_entites_by_pointer);}

class Player : public Creature
{
    private:
        static constexpr tools::POSf hitbox = {1, 0.5};
        static constexpr tools::POSf pointer_hitbox = {1, 2};

        static constexpr int max_hungry = 10000;
        static constexpr int max_thirst = 10000;

        using HAND_ACTION_TYPE = std::function<bool(__HAND_ACTION_ARGUMENTS)>;
        std::vector<HAND_ACTION_TYPE> main_hand_actions, off_hand_actions;
        float reach;

        void set_main_hand_actions(std::vector<HAND_ACTION_TYPE>&& main_hand_actions = {});
        void set_off_hand_actions(std::vector<HAND_ACTION_TYPE>&& off_hand_actions = {});

        int hungry, thirst;

    public:
        Player(const tools::POSf& pos = tools::POSf());

        void add_hungry(int value);
        int get_hungry() const;
        void add_thirst(int value);
        int get_thirst() const;

        virtual tools::POSf get_hitbox() const override;
        virtual tools::POSf get_pointer_hitbox() const override;

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;

        void set_reach(float reach);
        float get_reach() const;
        bool can_reach(const tools::POSf& pointer_pos, const World& world) const;

        bool interact(__HAND_ACTION_ARGUMENTS);
        bool sip(__HAND_ACTION_ARGUMENTS);

        bool main_hand_action(__HAND_ACTION_ARGUMENTS);
        bool off_hand_action(__HAND_ACTION_ARGUMENTS);
        
        virtual EntityName get_name() const override {return EntityName::player;}    

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Player, pos, size, entity_code, motion, ascendable_height, direction, max_health, health, power, time_for_attack, attack_distance, notice_distance, foot_state, reach);
};