#include "pointer.hpp"

Pointer::Pointer()
    : Entity({0,0}, 0.25)
    , __focus(false)
{}

void Pointer::focus(bool value) {__focus = value;}

bool Pointer::is_focusing() const {return __focus;}

tools::POSf Pointer::get_hitbox() const {return {size/2, size/2};}

void Pointer::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    (void)window_manager;
    (void)world_manager;
}
