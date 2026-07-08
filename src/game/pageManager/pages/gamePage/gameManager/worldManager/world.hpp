#pragma once

#include <vector>
#include "tools/pos.hpp"

class World
{
    public :
        enum class Tile
        {
            VOID = -1,
            GRASS_1, GRASS_2, GRASS_3,
            CULTIVATE,
            COUNT
        };
        using ELEMENT_TYPE = std::pair<Tile, int>;
        using WORLD_TYPE = std::vector<std::vector<ELEMENT_TYPE>>;
    private :
        WORLD_TYPE world;
        tools::POSs world_size;
    public :
        World();
        World(WORLD_TYPE&& world);

        void init(WORLD_TYPE&& world);

        tools::POSs get_size() const;

        bool in(tools::POSs&& pos) const;
        bool in(const tools::POSs& pos) const;

        Tile& operator[](tools::POSs&& pos);
        Tile& operator[](const tools::POSs& pos);
        const Tile& operator[](tools::POSs&& pos) const;
        const Tile& operator[](const tools::POSs& pos) const;

        int get_height(tools::POSs&& pos) const;
        int get_height(const tools::POSs& pos) const;
};