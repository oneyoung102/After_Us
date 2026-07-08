#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"
#include "tools/dir.hpp"

class MovingEntity : public Entity
{
    private :
        tools::POSf prev_pos;
    protected :
        static constexpr float DEFAULT_SPEED = 0.015;
        float speed;
        unsigned int threshold_height;

        tools::Direction direction;
    public :
        MovingEntity(const tools::POSf& pos, unsigned int size = 1, float speed = DEFAULT_SPEED, unsigned int threshold_height = 1);
        virtual ~MovingEntity() = default;

        tools::POSf get_prev_pos() const;
        void sync_prev_pos();

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

        tools::Direction get_direction() const;

        virtual bool is_moving_entity() const override {return true;}
};