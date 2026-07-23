#include "movingEntity.hpp"
#include "tools/dir.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include <cmath>

MovingEntity::MovingEntity(const tools::POSf& pos, float size, float speed, unsigned int ascendable_height)
    : Entity(pos, size)
    , ascendable_height(ascendable_height)
    , direction(tools::UP)
{
    set_speed(speed);
} 

void MovingEntity::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    (void)window_manager; 
    motion.accel();
    //if(motion.is_moving()) -> 발스테이트 = stop
}

tools::POSf MovingEntity::get_next_pos() const {return pos+motion.get_vector();}
bool MovingEntity::is_moving() const {return motion.is_moving();}
void MovingEntity::stop() {motion.stop();}

void MovingEntity::set_speed(float speed)
{
    motion.set_speed(speed);
}
float MovingEntity::get_speed() const {return motion.get_speed();}   

bool MovingEntity::is_moveable_to(const World& world, const tools::POSf& pos)
{
    const auto hitbox = get_hitbox();
    const auto start = tools::POSi(floor(pos.c - hitbox.c), floor(pos.r - hitbox.r));
    const auto end = tools::POSi(pos.c + hitbox.c, pos.r + hitbox.r);

    if(!world.in(start) || !world.in(end))
        return false;
    
    for(size_t r = start.r ; r <= end.r ; r++)
        for(size_t c = start.c ; c <= end.c ; c++)
            if(abs(world.get_height(pos)-world.get_height({c,r})) > ascendable_height)
                return false;
    return true;
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