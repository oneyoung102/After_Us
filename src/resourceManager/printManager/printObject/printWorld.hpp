#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

#include "main/windowManager/windowManager.hpp"
#include "resourceManager/printManager/printObject/printObject.hpp"
#include "resourceManager/printManager/shader/shader.hpp"
#include "tools/pos.hpp"
#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include <SFML/Graphics.hpp>


template<>
class PrintObject<World> : public PrintObjectInterface
{
    private :
        float scale;
        const ImageDatas::IMAGE_DATA& world_image_data;
        const World& world;
        const Camera& camera;

        void print_tile(sf::RenderWindow& w, Shader& shader, const tools::POSf& screen_pos, World::Tile tile_code)
        {
            if(tile_code == WorldImageData::CroppedImageName::VOID)
                return;
            const auto tex_pos = world_image_data[tile_code];
            const auto tex_size = world_image_data.size();
            
            sf::Sprite tile_sprite = world_image_data.get_sprite();
            tile_sprite.setScale({scale, scale});
            tile_sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {tex_size.x, tex_size.y}));        
            print_sprite(w,tile_sprite,screen_pos,shader);
        }
    public :
        PrintObject(const ImageDatas& image_datas, const WorldManager& world_manager)
            : PrintObjectInterface(image_datas)
            , scale(0)
            , world_image_data(image_datas[ImageDatas::Name::world])
            , world(world_manager.get_world())
            , camera(world_manager.get_camera())
        {}

        virtual void print(sf::RenderWindow& w, Shader& shader) override
        {
            scale = WindowManager::get_scale(camera);

            const auto [start,end] = WindowManager::get_displayed_world_range(world,camera);
            const auto scaled_tile_size = world_image_data.size(scale);
            const auto world_origin_in_screen = WindowManager::get_pixel_world_origin(camera);

            for (int r = start.r; r < end.r; ++r)
                for (int c = start.c; c < end.c; ++c)
                {
                    const auto npos = tools::POSi(c, r);
                    const auto draw_pos = world_origin_in_screen + (tools::POSf(npos) * scaled_tile_size);
                    const auto tile_code = world[tools::POSs(npos)];

                    shader.set_brightness(shader.get_brightness_by_height(world.get_height(npos), world.get_height(camera.get_pos())));
                    print_tile(w, shader, draw_pos, tile_code);
                }
                
            if(is_alive())
                --life;
        }
};