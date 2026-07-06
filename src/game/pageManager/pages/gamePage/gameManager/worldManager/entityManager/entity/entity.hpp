#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"
#include "tools/pos.hpp"

class Entity
{
    public :
        using ENTITY_CODE = unsigned long long;
        constexpr static Entity::ENTITY_CODE UNREGISTERED = 0;
        enum class EntityName
        {
            camera,
            player,
            COUNT
        };
    protected :
        tools::POSf pos;
        float size;
        ENTITY_CODE entity_code;
    public :
        Entity(const tools::POSf& pos, float size = 1.f);
        virtual ~Entity() = default;

        virtual tools::POSf get_pos() const;
        float get_size() const;

        void set_pos(const tools::POSf& pos);
        void set_pos(const tools::POSf&& pos);
        void set_size(float size);

        World::TILE get_curr_tile(const World& world) const;
        int get_curr_height(const World& world) const;

        bool is_registered() const;
        ENTITY_CODE get_entity_code() const;
        void set_entity_code(ENTITY_CODE entity_code);

        virtual EntityName get_name() const = 0;

        inline bool operator==(const Entity& entity) const {return entity_code == entity.entity_code;}
};

