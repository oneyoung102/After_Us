#pragma once

#include "game/pages/gamePage/gameManager/world/worldManager.hpp"
#include "resourceManager/printManager/printObject/printObject.hpp"
#include "tools/pos.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include <SFML/Graphics.hpp>


template<>
class PrintObject<WorldManager> : public PrintObjectInterface
{
    private :
        float scale;
        const WorldManager& world_manager;
        const tools::POSf screen_size;

        void print_tile(sf::RenderWindow& w, const tools::POSf& screen_pos, World::TILE tile_code)
        {
            if(tile_code == image_constant::VOID)
                return;
            const auto tex_pos = image_constant::TILE_POS[tile_code] * image_constant::TILE_SIZE;
            sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {image_constant::TILE_SIZE.x, image_constant::TILE_SIZE.y})); 
            print_sprite(w,screen_pos);
        }
    public :
        PrintObject(const WorldManager& world_manager, const tools::POSf& screen_size, sf::Sprite s)
            : PrintObjectInterface(s)
            , world_manager(world_manager)
            , screen_size(screen_size)
        {}

        void print(sf::RenderWindow& w) override
        {
            scale = 4.0f/world_manager.get_camera().getHeight();
            sprite.setScale({scale,scale});

            const auto scaled_tile_size = image_constant::TILE_SIZE*scale;
            const auto showed_world_size = tools::POSi(ceil(screen_size.x/scaled_tile_size.x),ceil(screen_size.y/scaled_tile_size.y));
            
            const auto camera_pos = world_manager.get_camera().get_pos();
            const auto world_screen_origin = (screen_size / 2.f) - (camera_pos * scaled_tile_size);

            const auto start = tools::POSi(floor(camera_pos.x - showed_world_size.x / 2.f), floor(camera_pos.y - showed_world_size.y / 2.f));
            const auto end = tools::POSi(ceil(camera_pos.x + showed_world_size.x / 2.f), ceil(camera_pos.y + showed_world_size.y / 2.f));

            for (int r = start.r; r < end.r; ++r)
                for (int c = start.c; c < end.c; ++c)
                {
                    const auto npos = tools::POSi(c, r);
                    if(world_manager.get_world().in(npos))
                    {
                        const auto draw_pos = world_screen_origin + (tools::POSf(npos) * scaled_tile_size);
                        const auto tile_code = world_manager.get_world()[npos];
                        const auto test_tile_code = image_constant::TileCode((((long long)r*c+3*c+c*c+r*7)^3721873)%3);
                        print_tile(w, draw_pos, test_tile_code);
                    }
                }
        }
};