#include "thing.hpp"

Thing::Thing(const tools::POSf& pos, const unsigned int size)
    : pos(pos)
    , size(size)
    , thing_code(UNREGISTERED)
{}

tools::POSf Thing::get_pos() const {return pos;}
unsigned int Thing::get_size() const {return size;}

void Thing::set_pos(const tools::POSf& pos){this->pos = pos;}
void Thing::set_pos(const tools::POSf&& pos){this->pos = std::move(pos);}
void Thing::set_size(unsigned int size){this->size = size;}

World::TILE Thing::get_curr_tile(const World& world) const
{
    return world[tools::POSs(pos)];
}
int Thing::get_curr_height(const World& world) const
{
    return world.get_height(tools::POSs(pos));
}

bool Thing::is_registered() const {return thing_code != UNREGISTERED;}
Thing::THING_CODE Thing::get_thing_code() const {return thing_code;}
void Thing::set_thing_code(Thing::THING_CODE thing_code)
{
    if(is_registered())
        throw std::runtime_error("thing is already registered");
    this->thing_code = thing_code;
}