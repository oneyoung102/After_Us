#pragma once

#include "game/pages/gamePage/gameManager/thing/things/camera.hpp"
#include "game/pages/gamePage/gameManager/world/world.hpp"
#include "tools/dir.hpp"

class WorldManager
{
    private :
        World world;
        Camera camera;
    public :
        WorldManager(Camera&& camera);

        const World& get_world() const;
        World& get_world();

        const Camera& get_camera() const;
        Camera& get_camera(); 

        void testCameraMove() {camera.move(camera.get_pos()+tools::POSf(0.03f,0.03f));}
};