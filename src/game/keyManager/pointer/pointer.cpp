#include "pointer.hpp"

Pointer::Pointer()
    : Entity({0,0}, 0.25)
    , __focus(false)
{}

void Pointer::focus(bool value) {__focus = value;}

bool Pointer::is_focusing() const {return __focus;}

void Pointer::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    (void)window_manager;
    (void)world_manager;
}

tools::POSf Pointer::get_hitbox() const {return hitbox*size;}
tools::POSf Pointer::get_pointer_hitbox() const {return pointer_hitbox*size;}

bool Pointer::is_collided(const Entity& entity, const World& world) const
{
    const auto pointer_hitbox1 = this->get_pointer_hitbox()/2.0;
    const auto pointer_hitbox2 = entity.get_pointer_hitbox()/2.0;
    const tools::POSf centered_pos1 = this->get_pos();
    const tools::POSf centered_pos2 = entity.get_pos()-tools::POSf(0,pointer_hitbox2.y);

    const tools::POSf rect_min1 = centered_pos1-pointer_hitbox1;
    const tools::POSf rect_max1 = centered_pos1+pointer_hitbox1;
    const tools::POSf rect_min2 = centered_pos2-pointer_hitbox2;
    const tools::POSf rect_max2 = centered_pos2+pointer_hitbox2;
    if(rect_max1.x < rect_min2.x || rect_max2.x < rect_min1.x)
        return false;
    if(rect_max1.y < rect_min2.y || rect_max2.y < rect_min1.y)
        return false;
    return true;
}