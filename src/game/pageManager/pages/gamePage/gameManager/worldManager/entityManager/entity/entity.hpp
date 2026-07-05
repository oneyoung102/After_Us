#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"
#include "tools/pos.hpp"

class Thing
{
    public :
        using THING_CODE = unsigned long long;
        constexpr static Thing::THING_CODE UNREGISTERED = 0;
        enum class ThingName
        {
            camera,
            COUNT
        };
    protected :
        tools::POSf pos;
        unsigned int size;
        THING_CODE thing_code;
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

        bool is_registered() const;
        THING_CODE get_thing_code() const;
        void set_thing_code(THING_CODE thing_code);

        virtual ThingName get_name() const = 0;

        inline bool operator==(const Thing& thing) const {return thing_code == thing.thing_code;}
};

