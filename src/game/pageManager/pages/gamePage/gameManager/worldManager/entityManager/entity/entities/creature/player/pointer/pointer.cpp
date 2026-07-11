#include "pointer.hpp"

Pointer::Pointer(const Entity& center)
    : Entity({0,0},0.25)
    , center(center)
    , reach(2.25)
    , focus(false)
{}

void Pointer::set_reach(float reach)
{
    if(reach < 0)
        throw std::runtime_error("reach of pointer must be positive");
    this->reach = reach;
}

bool Pointer::is_focusing() const {return focus;}

float Pointer::get_reach() const {return reach;}

tools::POSf Pointer::get_center_pos() const
{
    return center.get_pos();
}

void Pointer::update(const WindowManager& window_manager, const Camera& camera)
{
    focus = window_manager.left_mouse_click() || window_manager.right_mouse_click();

    auto anchor_pos = center.get_pos() + tools::POSf(0, -0.375f);
    auto clamped_pos = window_manager.get_mouse_pos(anchor_pos, reach, camera);
    set_pos(clamped_pos);
}
