#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"

class MovingEntity : public Entity
{
    protected :
        static constexpr float DEFAULT_SPEED = 3.0f/128.0f;
        float speed;
        unsigned int threshold_height;
    public :
        MovingEntity(const tools::POSf& pos, unsigned int size = 1, float speed = DEFAULT_SPEED, unsigned int threshold_height = 1);
        virtual ~MovingEntity() = default;

        float get_speed() const;
        void set_speed(float speed);

        void move(const tools::POSf& pos);
        void move(tools::POSf&& pos);
        void move_minimum_distance(const tools::POSf& pos) = delete;
        bool movable(const World& world, const tools::POSf& pos);

        void move_left();
        void move_right();
        void move_up();
        void move_down();
};