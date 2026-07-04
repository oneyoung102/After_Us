#include "livingThing.hpp"

LivingThing::LivingThing(const tools::POSf& pos,
            unsigned int size,
            float speed,
            unsigned int threshold_height,
            int max_health,
            int health,
            int power,
            int attack_speed,
            float attack_distance,
            float notice_distance)
    : MovingThing(pos, size, speed, threshold_height)
{
    set_max_health(max_health);
    set_health(health);
    set_power(power);
    set_attack_speed(attack_speed);
    set_attack_distance(attack_distance);
    set_notice_distance(notice_distance);
}

bool LivingThing::is_alive() const {return health > 0;}

int LivingThing::get_max_health() const {return max_health;}
void LivingThing::set_max_health(int max_health)
{
    if(max_health < 0)
        throw std::runtime_error("max health can't be negative");
    this->max_health = max_health;
    set_health(health);
}

int LivingThing::get_health() const {return health;}
void LivingThing::set_health(int health)
{
    if(health > max_health)
        throw std::runtime_error("health can't be over max health");
    if(health < 0)
        throw std::runtime_error("health can't be negative");
    this->health = health;
}
void LivingThing::add_health(int health)
{
    this->health = std::max(0, std::min(max_health, this->health + health));
}

int LivingThing::get_power() const {return power;}
void LivingThing::set_power(int power){this->power = power;}

int LivingThing::get_attack_speed() const {return attack_speed;}
void LivingThing::set_attack_speed(int attack_speed)
{
    if(attack_speed < 0)
        throw std::runtime_error("attack_speed can't be negative");
    this->attack_speed = attack_speed;
}

float LivingThing::get_attack_distance() const {return attack_distance;}
void LivingThing::set_attack_distance(float attack_distance)
{
    if(attack_distance < 0)
        throw std::runtime_error("attack_distance can't be negative");
    this->attack_distance = attack_distance;
}

float LivingThing::get_notice_distance() const {return notice_distance;}
void LivingThing::set_notice_distance(float notice_distance)
{
    if(notice_distance < 0)
        throw std::runtime_error("notice_distance can't be negative");
    this->notice_distance = notice_distance;
}

bool LivingThing::noticeable(const Thing& thing) const
{
    const auto dpos = pos-thing.get_pos();
    return dpos*dpos <= notice_distance*notice_distance;
}
bool LivingThing::attackable(const LivingThing& thing) const
{
    const auto dpos = pos-thing.get_pos();
    return dpos*dpos <= attack_distance*attack_distance;
}
void LivingThing::attack(LivingThing& thing) const {thing.add_health(power);}

void LivingThing::target(std::shared_ptr<LivingThing> target){ __target = target;}
void LivingThing::untarget(){ __target.reset();}