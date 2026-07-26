#include "thing.hpp"

Thing::Thing(const tools::POSf& pos, float size, ThingName thing_name)
    : Entity(pos, size)
    , thing_name(thing_name)
{}

Thing::ThingName Thing::get_thing_name() const
{
    return thing_name;
}