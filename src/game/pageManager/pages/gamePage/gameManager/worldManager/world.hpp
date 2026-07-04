#pragma once

#include <vector>
#include "tools/pos.hpp"
#include "resourceManager/fileManager/imageData/imageDatas.hpp"

class World
{
    public :
        using TILE = WorldImageData::CroppedImageName;
        using ELEMENT_TYPE = std::pair<TILE, int>;
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

        TILE& operator[](tools::POSs&& pos);
        TILE& operator[](const tools::POSs& pos);
        const TILE& operator[](tools::POSs&& pos) const;
        const TILE& operator[](const tools::POSs& pos) const;

        int get_height(tools::POSs&& pos) const;
        int get_height(const tools::POSs& pos) const;
};