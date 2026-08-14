#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/movingEntity/movingEntity.hpp"
#include "tools/tick.hpp"
#include <memory>

class WindowManager;
class WorldManager;

class Creature : public MovingEntity
{
    public :
        enum class FootState
        {
            stop,
            left_foot,
            right_foot,
            COUNT
        };
        enum class MovingState
        {
            DOWN_1, DOWN_2, DOWN_3,
            UP_1, UP_2, UP_3,
            RIGHT_1, RIGHT_2, RIGHT_3,
            LEFT_1, LEFT_2, LEFT_3,
            COUNT
        };
    protected :
        int max_health, health;

        int power;
        tools::Tick time_for_attack;
        float attack_distance;
        std::weak_ptr<const Creature> __target;

        float notice_distance;
        
        FootState foot_state;
        
    public :
        Creature(const tools::POSf& pos = tools::POSf(),
            float size = 1.f,
            float speed = 0.015f,
            unsigned int ascendable_height = 1,
            int max_health = 100,
            int health = 100,
            int power = 10,
            tools::Tick attack_speed = 10,
            float attack_distance = 1.f,
            float notice_distance = 5.f);
        virtual ~Creature() = default;
        
        MovingState get_moving_state() const;

        bool is_alive() const;

        int get_max_health() const;
        void set_max_health(int max_health);

        int get_health() const;
        void set_health(int health);
        void add_health(int health);

        int get_power() const;
        void set_power(int power);

        int get_time_for_attack() const;
        void set_time_for_attack(int attack_speed);

        float get_attack_distance() const;
        void set_attack_distance(float attack_distance);

        float get_notice_distance() const;
        void set_notice_distance(float notice_distance);

        bool noticeable(std::weak_ptr<const Entity> entity) const;
        bool attackable(std::weak_ptr<const Creature> entity) const;
        void attack(std::weak_ptr<Creature> entity) const;
        void target(std::shared_ptr<const Creature> target);
        void untarget();

        virtual bool is_creature() const override {return true;}
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Creature, pos, size, entity_code, motion, ascendable_height, direction, max_health, health, power, time_for_attack, attack_distance, notice_distance);
};


