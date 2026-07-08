#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"
#include <stdexcept>

World::World()
    : world(WORLD_TYPE(1000, std::vector<ELEMENT_TYPE>(1000, {Tile::GRASS_1, 0})))
    , world_size(tools::POSs(1000, 1000))
{}

World::World(WORLD_TYPE&& world)
    : world(std::move(world))
    , world_size(tools::POSs(this->world.size(), this->world.empty() ? 0 : this->world[0].size()))
{}

void World::init(WORLD_TYPE&& world)
{
    this->world = std::move(world);
    this->world_size = tools::POSs(this->world.size(), this->world.empty() ? 0 : this->world[0].size());
}


tools::POSs World::get_size() const {return world_size;}

bool World::in(tools::POSs&& pos) const
{
    return tools::POSs() <= pos && pos < world_size;
}

bool World::in(const tools::POSs& pos) const
{
    return tools::POSs() <= pos && pos < world_size;
}

World::Tile& World::operator[](tools::POSs&& pos)
{
    if(!in(std::move(pos)))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].first;
}
World::Tile& World::operator[](const tools::POSs& pos)
{
    if(!in(pos))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].first;
}
const World::Tile& World::operator[](tools::POSs&& pos) const
{
    if(!in(std::move(pos)))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].first;
}
const World::Tile& World::operator[](const tools::POSs& pos) const
{
    if(!in(pos))
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
    if(!in(pos))
        throw std::runtime_error("out of World");
    return world[pos.r][pos.c].second;
}