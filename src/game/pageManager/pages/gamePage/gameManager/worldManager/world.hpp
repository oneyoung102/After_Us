#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include "tools/pos.hpp"

class Tile
{
    public:
        enum class TileName
        {
            VOID = -1,
            GRASS, DIRT, SAND, GRAVEL,
            WATER, WATER_2nd_FRAME, WATER_3rd_FRAME, WATER_4th_FRAME, WATER_5th_FRAME, WATER_6th_FRAME, WATER_7th_FRAME, WATER_8th_FRAME,
            CULTIVATE, STONE_BRICK,
            COUNT
        };
        TileName name;
        int height;

        Tile(TileName name = TileName::VOID, int height = 0)
            : name(name)
            , height(height)
        {}
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Tile, name, height)
};

NLOHMANN_JSON_SERIALIZE_ENUM(Tile::TileName, {
    {Tile::TileName::VOID, "VOID"},
    {Tile::TileName::GRASS, "GRASS"},
    {Tile::TileName::DIRT, "DIRT"},
    {Tile::TileName::SAND, "SAND"},
    {Tile::TileName::GRAVEL, "GRAVEL"},
    {Tile::TileName::WATER, "WATER"},
    {Tile::TileName::WATER_2nd_FRAME, "WATER_2nd_FRAME"},
    {Tile::TileName::WATER_3rd_FRAME, "WATER_3rd_FRAME"},
    {Tile::TileName::WATER_4th_FRAME, "WATER_4th_FRAME"},
    {Tile::TileName::WATER_5th_FRAME, "WATER_5th_FRAME"},
    {Tile::TileName::WATER_6th_FRAME, "WATER_6th_FRAME"},
    {Tile::TileName::WATER_7th_FRAME, "WATER_7th_FRAME"},
    {Tile::TileName::WATER_8th_FRAME, "WATER_8th_FRAME"},
    {Tile::TileName::CULTIVATE, "CULTIVATE"},
    {Tile::TileName::STONE_BRICK, "STONE_BRICK"},
    {Tile::TileName::COUNT, "COUNT"} 
})


class World
{
    public :
        using WORLD_TYPE = std::vector<std::vector<Tile>>;
    private :
        tools::POSs world_size;
        WORLD_TYPE world;
    public :
        World();
        World(WORLD_TYPE&& world);

        void init(WORLD_TYPE&& world);

        tools::POSs get_size() const;

        bool in(tools::POSf&& pos) const;
        bool in(const tools::POSf& pos) const;

        Tile& operator[](tools::POSs&& pos);
        Tile& operator[](const tools::POSs& pos);
        const Tile& operator[](tools::POSs&& pos) const;
        const Tile& operator[](const tools::POSs& pos) const;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(World, world_size, world)
};