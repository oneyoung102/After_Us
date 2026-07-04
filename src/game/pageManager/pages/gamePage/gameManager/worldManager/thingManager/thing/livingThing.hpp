#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/thingManager/thing/movingThing.hpp"

class LivingThing : public MovingThing
{
    private :
        int max_health, health;

        int power;
        int attack_speed; //Tick class가 추가되면 바꿀 거임
        float attack_distance;
        std::weak_ptr<LivingThing> __target;

        float notice_distance;
        
    public :
        LivingThing(const tools::POSf& pos,
            unsigned int size,
            float speed,
            unsigned int threshold_height,
            int max_health,
            int health,
            int power,
            int attack_speed,
            float attack_distance,
            float notice_distance);
        virtual ~LivingThing() = default;

        bool is_alive() const;

        int get_max_health() const;
        void set_max_health(int max_health);

        int get_health() const;
        void set_health(int health);
        void add_health(int health);

        int get_power() const;
        void set_power(int power);

        int get_attack_speed() const;
        void set_attack_speed(int attack_speed);

        float get_attack_distance() const;
        void set_attack_distance(float attack_distance);

        float get_notice_distance() const;
        void set_notice_distance(float notice_distance);

        bool noticeable(const Thing& thing) const;
        bool attackable(const LivingThing& thing) const;
        void attack(LivingThing& thing) const;

        void target(std::shared_ptr<LivingThing> target);
        void untarget();
};