#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/movingEntity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class Camera : public MovingEntity
{
    public : 
        static constexpr float INITIAL_ALTITUDE = 4.f;
    private :
        std::weak_ptr<const Entity> tracing_entity;
        float altitude;
    public : 
        Camera(std::shared_ptr<Entity> entity = nullptr);
        void target(std::shared_ptr<Entity> entity);
        void untarget();

        void trace();

        virtual tools::POSf get_pos() const override;

        void rise(float altitude);
        void set_altitude(float altitude = INITIAL_ALTITUDE);
        float get_altitude() const;

        bool has_target() const;

        virtual EntityName get_name() const override { return EntityName::camera; }
};