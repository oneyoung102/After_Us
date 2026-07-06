#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/movingEntity.hpp"
#include "main/windowManager/tick.hpp"

class Creature : public MovingEntity
{
    private :
        int max_health, health;

        int power;
        Tick time_for_attack;
        float attack_distance;
        std::weak_ptr<const Creature> __target;

        float notice_distance;
        
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

        void target(std::shared_ptr<Creature> target);
        void untarget();
};