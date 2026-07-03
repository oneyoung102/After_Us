#pragma once

#include "game/pages/gamePage/gameManager/world/world.hpp"
#include "tools/pos.hpp"

class Thing
{
    protected :
        tools::POSf pos;
        unsigned int size;
    public :
        Thing(const tools::POSf& pos, const unsigned int size = 1);
        virtual ~Thing() = default;

        virtual tools::POSf get_pos() const;
        unsigned int get_size() const;

        void set_pos(const tools::POSf& pos);
        void set_pos(const tools::POSf&& pos);
        void set_size(unsigned int size);

        World::TILE get_curr_tile(const World& world) const;
        int get_curr_height(const World& world) const;
};

