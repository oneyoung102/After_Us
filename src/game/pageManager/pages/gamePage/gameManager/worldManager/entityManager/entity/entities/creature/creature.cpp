#include "creature.hpp"

Creature::Creature(const tools::POSf& pos,
            float size,
            float speed,
            unsigned int threshold_height,
            int max_health,
            int health,
            int power,
            Tick time_for_attack,
            float attack_distance,
            float notice_distance)
    : MovingEntity(pos, size, speed, threshold_height)
{
    set_max_health(max_health);
    set_health(health);
    set_power(power);
    set_time_for_attack(time_for_attack);
    set_attack_distance(attack_distance);
    set_notice_distance(notice_distance);
}

bool Creature::is_alive() const {return health > 0;}

int Creature::get_max_health() const {return max_health;}
void Creature::set_max_health(int max_health)
{
    if(max_health < 0)
        throw std::runtime_error("max health can't be negative");
    this->max_health = max_health;
    set_health(health);
}

int Creature::get_health() const {return health;}
void Creature::set_health(int health)
{
    if(health > max_health)
        throw std::runtime_error("health can't be over max health");
    if(health < 0)
        throw std::runtime_error("health can't be negative");
    this->health = health;
}
void Creature::add_health(int health)
{
    this->health = std::max(0, std::min(max_health, this->health + health));
}

int Creature::get_power() const {return power;}
void Creature::set_power(int power){this->power = power;}

int Creature::get_time_for_attack() const {return time_for_attack;}
void Creature::set_time_for_attack(int attack_speed)
{
    if(attack_speed < 0)
        throw std::runtime_error("attack_speed can't be negative");
    this->time_for_attack = attack_speed;
}

float Creature::get_attack_distance() const {return attack_distance;}
void Creature::set_attack_distance(float attack_distance)
{
    if(attack_distance < 0)
        throw std::runtime_error("attack_distance can't be negative");
    this->attack_distance = attack_distance;
}

float Creature::get_notice_distance() const {return notice_distance;}
void Creature::set_notice_distance(float notice_distance)
{
    if(notice_distance < 0)
        throw std::runtime_error("notice_distance can't be negative");
    this->notice_distance = notice_distance;
}

bool Creature::noticeable(std::weak_ptr<const Entity> entity) const
{
    const auto dpos = pos-entity.lock()->get_pos();
    return dpos*dpos <= notice_distance*notice_distance;
}
bool Creature::attackable(std::weak_ptr<const Creature> entity) const
{
    const auto dpos = pos-entity.lock()->get_pos();
    return dpos*dpos <= attack_distance*attack_distance;
}
void Creature::attack(std::weak_ptr<Creature> entity) const {entity.lock()->add_health(power);}

void Creature::target(std::shared_ptr<Creature> target){ __target = target;}
void Creature::untarget(){ __target.reset();}