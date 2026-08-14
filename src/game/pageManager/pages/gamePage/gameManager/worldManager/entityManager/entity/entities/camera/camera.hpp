#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/movingEntity/movingEntity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"
#include <memory>

class WindowManager;
class WorldManager;

class Camera : public MovingEntity
{
    public : 
        static constexpr float INITIAL_ALTITUDE = 4.f;
    private :
        std::weak_ptr<const Entity> tracing_entity;
        float altitude;

        static constexpr tools::POSf hitbox = {0.0, 0.0};
        static constexpr tools::POSf pointer_hitbox = {0.0, 0.0};

    public : 
        Camera(std::shared_ptr<const Entity> entity = nullptr);

        tools::POSf get_pos() const;
        tools::POSf get_target_pos() const;

        virtual tools::POSf get_hitbox() const override;
        virtual tools::POSf get_pointer_hitbox() const override;

        
        void target(std::shared_ptr<const Entity> entity);
        void untarget();

        void trace();

        void rise(float altitude);
        void set_altitude(float altitude = INITIAL_ALTITUDE);
        float get_altitude() const;

        bool has_target() const;

        virtual EntityName get_name() const override { return EntityName::camera; }

        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override
        {
            MovingEntity::update(window_manager, world_manager);
        }

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Camera, pos, size, entity_code, motion, ascendable_height, direction, altitude);
};