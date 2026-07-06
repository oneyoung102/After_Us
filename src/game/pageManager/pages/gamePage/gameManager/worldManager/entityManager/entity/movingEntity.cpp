#include "movingEntity.hpp"
#include "tools/dir.hpp"

MovingEntity::MovingEntity(const tools::POSf& pos, unsigned int size, float speed, unsigned int threshold_height)
    : Entity(pos, size)
    , threshold_height(threshold_height)
{
    set_speed(speed);
} 

void MovingEntity::set_speed(float speed)
{
    this->speed = fmax(0,speed);
}
float MovingEntity::get_speed() const {return speed;}   

void MovingEntity::move(const tools::POSf& pos)
{
    this->pos = pos;
}

void MovingEntity::move(tools::POSf&& pos)
{
    this->pos = std::move(pos);
}

bool MovingEntity::movable(const World& world, const tools::POSf& pos)
{
    if(!world.in(pos))
        return false;
    return abs(world.get_height(pos)-get_curr_height(world)) <= threshold_height;
}

void MovingEntity::move_left()  {move(pos + tools::POSf(tools::DIR[tools::LEFT])*speed);} //현재는 임시방편이고 나중에 행동 클래스 만들면 큐에 넣고 순차적으로 돌리든지 할 거임
void MovingEntity::move_right() {move(pos + tools::POSf(tools::DIR[tools::RIGHT])*speed);}
void MovingEntity::move_up()    {move(pos + tools::POSf(tools::DIR[tools::UP])*speed);}
void MovingEntity::move_down()  {move(pos + tools::POSf(tools::DIR[tools::DOWN])*speed);}