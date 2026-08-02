#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"
#include "tools/json.hpp"
#include <stdexcept>

World::World()
{}

World::World(WORLD_TYPE&& world)
    : world(std::move(world))
    , world_size(tools::POSs(world.size(), world.empty() ? 0 : world[0].size()))
{}

void World::init(WORLD_TYPE&& world)
{
    this->world = std::move(world);
    this->world_size = tools::POSs(this->world.size(), this->world.empty() ? 0 : this->world[0].size());
}


tools::POSs World::get_size() const {return world_size;}

bool World::in(tools::POSf&& pos) const
{
    return tools::POSf() <= pos && pos < world_size;
}

bool World::in(const tools::POSf& pos) const
{
    return tools::POSf() <= pos && pos < world_size;
}

Tile& World::operator[](tools::POSs&& pos)
{
    if(!in(std::move(pos)))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c];
}Tile& World::operator[](const tools::POSs& pos)
{
    if(!in(pos))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c];
}
const Tile& World::operator[](tools::POSs&& pos) const
{
    if(!in(std::move(pos)))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c];
}
const Tile& World::operator[](const tools::POSs& pos) const
{
    if(!in(pos))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c];
}