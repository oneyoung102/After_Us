#include "thing.hpp"

Thing::Thing(const tools::POSf& pos, const unsigned int size)
    : pos(pos)
    , size(size)
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