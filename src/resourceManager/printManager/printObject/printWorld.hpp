#pragma once

#include "game/pages/gamePage/gameManager/world/worldManager.hpp"

#include "resourceManager/printManager/printObject/printObject.hpp"
#include "resourceManager/printManager/shader/shader.hpp"
#include "tools/cast.hpp"
#include "tools/pos.hpp"
#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include <SFML/Graphics.hpp>


template<>
class PrintObject<WorldManager> : public PrintObjectInterface
{
    private :
        float scale;
        const World& world;
        const Camera& camera;
        const tools::POSf screen_size;

        void print_tile(sf::RenderWindow& w, Shader& shader, const tools::POSf& screen_pos, World::TILE tile_code)
        {
            if(tile_code == WorldImageData::CroppedImageName::VOID)
                return;
            const auto& sub_data = image_data[tile_code];
            const auto tex_pos = sub_data.pos();
            const auto tex_size = sub_data.size(scale);
            sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {tex_size.x, tex_size.y})); 
            print_sprite(w,screen_pos,shader);
        }
    public :
        PrintObject(const ImageDatas::IMAGE_DATA& image_data, const World& world, const Camera& camera, const tools::POSf& screen_size)
            : PrintObjectInterface(image_data)
            , world(world)
            , camera(camera)
            , screen_size(screen_size)
        {}

        void print(sf::RenderWindow& w, Shader& shader) override
        {
            scale = 7.f/camera.get_altitude();
            sprite.setScale({scale,scale});

            const auto scaled_tile_size = image_data[WorldImageData::CroppedImageName::GRASS_1].size(scale);
            const auto showed_world_size = tools::POSi(ceil(screen_size.x/scaled_tile_size.x),ceil(screen_size.y/scaled_tile_size.y));
            
            const auto camera_pos = camera.get_pos();
            const auto world_origin_in_screen = (screen_size / 2.f) - (camera_pos * scaled_tile_size);

            const auto world_size = world.get_size();

            const tools::POSi start = tools::POSi(
                std::max(0, tools::CASTi(floor(camera_pos.x - showed_world_size.x / 2.f))),
                std::max(0, tools::CASTi(floor(camera_pos.y - showed_world_size.y / 2.f)))
            );
            const tools::POSi end = tools::POSi(
                std::min(tools::CASTi(world_size.c), tools::CASTi(ceil(camera_pos.x + showed_world_size.x / 2.f))),
                std::min(tools::CASTi(world_size.r), tools::CASTi(ceil(camera_pos.y + showed_world_size.y / 2.f)))
            );

            for (int r = start.r; r < end.r; ++r)
            {
                for (int c = start.c; c < end.c; ++c)
                {
                    const auto npos = tools::POSi(c, r);
                    const auto draw_pos = world_origin_in_screen + (tools::POSf(npos) * scaled_tile_size);
                    const auto tile_code = world[tools::POSs(npos)];

                    const auto test_tile_code = WorldImageData::CroppedImageName((((long long)r*c+3*c+c*c+r*7)^3721873)%3);
                    const int test_tile_height = world.get_height(npos)+(r+c);
                    const int test_cam_height = camera.get_curr_height(world)+((int)camera_pos.r+(int)camera_pos.c);
                    
                    shader.set_brightness(Shader::get_brightness_by_height(test_cam_height,test_tile_height));
                    print_tile(w, shader, draw_pos, test_tile_code);
                }
            }
        }
};