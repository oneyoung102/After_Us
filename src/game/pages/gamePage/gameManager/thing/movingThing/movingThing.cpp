#include "movingThing.hpp"

MovingThing::MovingThing(const tools::POSf& pos, unsigned int size, float speed, unsigned int threshold_height)
    : Thing(pos, size)
    , threshold_height(threshold_height)
{
    set_speed(speed);
} 

void MovingThing::set_speed(float speed)
{
    this->speed = fmax(0,speed);
}
float MovingThing::get_speed() const {return speed;}   

void MovingThing::move(const tools::POSf& pos)
{
    this->pos = pos;
}

void MovingThing::move(tools::POSf&& pos)
{
    this->pos = std::move(pos);
}

bool MovingThing::movable(const World& world, tools::Direction dir)
{
    const tools::POSf npos = pos+dir;
    if(!world.in(npos))
        return false;
    return abs(world.get_height(npos)-get_curr_height(world)) <= threshold_height;
}