#pragma once

#include "game/pages/gamePage/gameManager/thing/movingThing/movingThing.hpp"
#include "game/pages/gamePage/gameManager/thing/thing.hpp"

class Camera : public MovingThing
{
    private :
        std::weak_ptr<const Thing> tracing_thing;
        float altitude;
    public : 
        Camera(std::shared_ptr<Thing> thing = nullptr);
        void trace(std::shared_ptr<Thing> thing);

        virtual tools::POSf get_pos() const override;

        void rise(float altitude);
        void set_altitude(float altitude = 4);
        float get_altitude() const;

        bool is_tracing() const;
};