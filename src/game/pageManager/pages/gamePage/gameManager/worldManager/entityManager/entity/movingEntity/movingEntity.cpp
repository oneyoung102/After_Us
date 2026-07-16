#include "movingEntity.hpp"
#include "tools/dir.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include <cmath>

MovingEntity::MovingEntity(const tools::POSf& pos, tools::POSf size, float speed, unsigned int ascendable_height)
    : Entity(pos, size)
    , ascendable_height(ascendable_height)
    , prev_pos(pos)
    , direction(tools::UP)
{
    set_speed(speed);
} 

void MovingEntity::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    (void)window_manager;
    
    motion.accel();
    if(motion.is_moving())
    {
        prev_pos = pos;
        auto npos = pos+motion.get_vector();
        if(is_moveable_to(world_manager.get_world(),npos))
            move(std::move(npos));
        else
            motion.stop();
    }
    //if(motion.is_moving()) -> 발스테이트 = stop
}

tools::POSf MovingEntity::get_prev_pos() const {return prev_pos;}

void MovingEntity::set_speed(float speed)
{
    motion.set_speed(speed);
}
float MovingEntity::get_speed() const {return motion.get_speed();}   

void MovingEntity::move(const tools::POSf& pos) {this->pos = pos;}

void MovingEntity::move(tools::POSf&& pos) {this->pos = std::move(pos);}

bool MovingEntity::is_moveable_to(const World& world, const tools::POSf& pos)
{
    if(!world.in(pos))
        return false;
    return abs(world.get_height(pos)-world.get_height(this->pos)) <= ascendable_height;
}

tools::Direction MovingEntity::get_direction() const {return direction;}

void MovingEntity::move_left()
{
    direction = tools::LEFT;
    motion.add_direction(direction);
}

void MovingEntity::move_right()
{
    direction = tools::RIGHT;
    motion.add_direction(direction);
}

void MovingEntity::move_up()
{
    direction = tools::UP;
    motion.add_direction(direction);
}

void MovingEntity::move_down()
{
    direction = tools::DOWN;
    motion.add_direction(direction);
}