#include "camera.hpp"

Camera::Camera(std::shared_ptr<Thing> thing)
    : MovingThing(thing ? thing->get_pos() : tools::POSf(0.f, 0.f), 0)
    , tracing_thing(thing)
{
    set_altitude();
}

tools::POSf Camera::get_pos() const
{
    if(tracing_thing.lock())
        return tracing_thing.lock()->get_pos();
    return pos;
}

void Camera::trace(std::shared_ptr<Thing> thing)
{
    tracing_thing = thing;
    pos = tracing_thing.lock()->get_pos();
}
void Camera::untrace() {tracing_thing.reset();}

void Camera::rise(float altitude)
{
    this->altitude = std::max(0.1f, this->altitude+altitude);
}

void Camera::set_altitude(float altitude)
{
    this->altitude = altitude;
}

float Camera::get_altitude() const {return altitude;}

bool Camera::is_tracing() const {return !tracing_thing.expired();}