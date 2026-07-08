#include "camera.hpp"

Camera::Camera(std::shared_ptr<Entity> entity)
    : MovingEntity(entity ? entity->get_pos() : tools::POSf(0.f, 0.f), 0)
    , tracing_entity(entity)
{
    set_altitude();
}

void Camera::target(std::shared_ptr<Entity> entity)
{
    tracing_entity = entity;
    if(auto target = tracing_entity.lock())
        pos = target->get_pos();
}
void Camera::untarget() {tracing_entity.reset();}

void Camera::trace()
{
    if(auto target = tracing_entity.lock())
        pos += (target->get_pos() + tools::POSf{0.f, -1.f} - pos)/16;
}

void Camera::rise(float altitude)
{
    this->altitude = std::max(0.1f, this->altitude+altitude);
}

void Camera::set_altitude(float altitude)
{
    this->altitude = altitude;
}

float Camera::get_altitude() const {return altitude;}

bool Camera::has_target() const {return !tracing_entity.expired();}