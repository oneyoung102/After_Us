#include "game/pages/gamePage/gameManager/world/world.hpp"
#include <stdexcept>

World::World()
    : world_size(tools::POSs(1000,1000))
    , world(WORLD_TYPE(world_size.y,std::vector<ELEMENT_TYPE>(world_size.x,{WorldImageData::CroppedImageName::GRASS_1,0})))
{}

World::World(WORLD_TYPE&& world)
    : world(std::move(world))
    , world_size(tools::POSs(world.size(),world[0].size()))
{}


tools::POSs World::get_size() const {return world_size;}

bool World::in(tools::POSs&& pos) const
{
    return tools::POSs() <= pos && pos < world_size;
}

bool World::in(const tools::POSs& pos) const
{
    return tools::POSs() <= pos && pos < world_size;
}

World::TILE& World::operator[](tools::POSs&& pos)
{
    if(!in(std::move(pos)))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].first;
}
World::TILE& World::operator[](const tools::POSs& pos)
{
    if(in(pos))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].first;
}
const World::TILE& World::operator[](tools::POSs&& pos) const
{
    if(!in(std::move(pos)))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].first;
}
const World::TILE& World::operator[](const tools::POSs& pos) const
{
    if(in(pos))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].first;
}

int World::get_height(tools::POSs&& pos) const
{
    if(!in(std::move(pos)))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].second;
}

int World::get_height(const tools::POSs& pos) const
{
    if(in(pos))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].second;
}