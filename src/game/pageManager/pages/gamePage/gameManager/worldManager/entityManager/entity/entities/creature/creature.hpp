#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/movingEntity/movingEntity.hpp"
#include "main/windowManager/tick.hpp"
#include <memory>

class WindowManager;
class WorldManager;

class Creature : public MovingEntity
{
    private :
        int max_health, health;

        int power;
        Tick time_for_attack;
        float attack_distance;
        std::weak_ptr<const Creature> __target;

        float notice_distance;
        
        enum class FootState
        {
            stop,
            left_foot,
            right_foot,
            COUNT
        };
        FootState foot_state;
        
    public :
        Creature(const tools::POSf& pos,
            float size,
            float speed,
            unsigned int threshold_height,
            int max_health,
            int health,
            int power,
            Tick attack_speed,
            float attack_distance,
            float notice_distance);
        virtual ~Creature() = default;
        
        enum class MovingState
        {
            DOWN_1, DOWN_2, DOWN_3,
            UP_1, UP_2, UP_3,
            RIGHT_1, RIGHT_2, RIGHT_3,
            LEFT_1, LEFT_2, LEFT_3,
            COUNT
        };
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
};
