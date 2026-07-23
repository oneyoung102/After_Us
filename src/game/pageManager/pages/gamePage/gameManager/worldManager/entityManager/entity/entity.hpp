#pragma once

#include "tools/pos.hpp"

class WorldManager;
class WindowManager;

class Entity
{
    public :
        using ENTITY_CODE = unsigned long long;
        constexpr static Entity::ENTITY_CODE UNREGISTERED = 0;
        enum class EntityName
        {
            camera,
            player,
            pointer,
            fallen_item,
            COUNT
        };
    protected :
        tools::POSf pos;
        float size;
        ENTITY_CODE entity_code;
    public :
        Entity(const tools::POSf& pos, float size = 1.0);
        virtual ~Entity() = default;

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) {}

        tools::POSf get_pos() const;
        virtual tools::POSf get_hitbox() const = 0;
        float get_size() const;

        void set_pos(const tools::POSf& pos);
        void set_pos(tools::POSf&& pos);
        void set_size(float size);

        bool is_registered() const;
        ENTITY_CODE get_entity_code() const;
        void set_entity_code(ENTITY_CODE entity_code);

        bool is_collided(const Entity& entity) const;

        virtual EntityName get_name() const = 0;

        inline bool operator==(const Entity& entity) const {return entity_code == entity.entity_code;}

        virtual bool is_camera() const {return false;}
        virtual bool is_creature() const {return false;}
        virtual bool is_fallen_item() const {return false;}
        virtual bool is_player() const {return false;}
        virtual bool is_interactable_entity() const {return false;}
        virtual bool is_moving_entity() const {return false;}

        bool is_dynamic_entity() const {return is_interactable_entity() || is_moving_entity();}
        bool is_static_entity() const {return !is_dynamic_entity();}
};

