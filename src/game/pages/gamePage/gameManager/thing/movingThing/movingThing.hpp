#pragma once

#include "game/pages/gamePage/gameManager/thing/thing.hpp"
#include "game/pages/gamePage/gameManager/world/world.hpp"
#include "tools/dir.hpp"

class MovingThing : public Thing
{
    private :
        float speed;
        unsigned int threshold_height;
    public :
        MovingThing(const tools::POSf& pos, unsigned int size = 1, float speed = 0.125, unsigned int threshold_height = 1);
        virtual ~MovingThing() = default;

        float get_speed() const;
        void set_speed(float speed);

        void move(const tools::POSf& pos);
        void move(tools::POSf&& pos);

        bool movable(const World& world, tools::Direction dir);

};