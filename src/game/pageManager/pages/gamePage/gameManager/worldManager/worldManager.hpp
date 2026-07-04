#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/thingManager/thingManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/thingManager/thing/things/camera.hpp"

class WorldManager
{
    private :
        World world;
        ThingManager thing_manager;
        Camera camera;
    public :
        WorldManager(Camera&& camera);

        const World& get_world() const;
        World& get_world();

        const Camera& get_camera() const;
        Camera& get_camera(); 

        const ThingManager& get_thing_manager() const;
        ThingManager& get_thing_manager();

        void testCameraMove() {camera.move(camera.get_pos()+tools::POSf(0.03f,0.03f));}
};