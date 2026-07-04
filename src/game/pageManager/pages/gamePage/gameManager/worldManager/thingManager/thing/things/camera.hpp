#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/thingManager/thing/movingThing.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/thingManager/thing/thing.hpp"

class Camera : public MovingThing
{
    public : 
        static constexpr float INITIAL_ALTITUDE = 4.f;
    private :
        std::weak_ptr<const Thing> tracing_thing;
        float altitude;
    public : 
        Camera(std::shared_ptr<Thing> thing = nullptr);
        void trace(std::shared_ptr<Thing> thing);
        void untrace();

        virtual tools::POSf get_pos() const override;

        void rise(float altitude);
        void set_altitude(float altitude = INITIAL_ALTITUDE);
        float get_altitude() const;

        bool is_tracing() const;

        virtual ThingName get_name() const override { return ThingName::camera; }
};