#pragma once

#include "tools/dir.hpp"
#include <queue>

class AcceleratedMotion
{
    private :
        static constexpr float BASIC_MAX_ACCELERATION = 0.025;

        static constexpr float MAX_POWER = 1;
        static constexpr float POWER_LESS = 0.075;
        static constexpr float POWER_GRADIANCE = 0.05;

        float speed;

        tools::POSf power;
        std::queue<tools::Direction> directions;
        
    public :
        AcceleratedMotion(float speed = BASIC_MAX_ACCELERATION);
        
        void accel();
        void add_direction(tools::Direction dir);
        tools::POSf get_vector() const;

        void stop();
        bool is_moving() const;

        void set_speed(float speed);
        float get_speed() const;
};