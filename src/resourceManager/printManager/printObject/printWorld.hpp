#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

#include "main/windowManager/windowManager.hpp"
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
        const WorldManager& world_manager;

        void print_tile(sf::RenderWindow& w, Shader& shader, const tools::POSf& screen_pos, World::TILE tile_code)
        {
            if(tile_code == WorldImageData::CroppedImageName::VOID)
                return;
            const auto tex_pos = image_data[tile_code];
            const auto tex_size = image_data.size();
            sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {tex_size.x, tex_size.y}));        
            print_sprite(w,screen_pos,shader);
        }
    public :
        PrintObject(const ImageDatas::IMAGE_DATA& image_data, const WorldManager& world_manager)
            : PrintObjectInterface(image_data)
            , world_manager(world_manager)
        {}

        virtual void print(sf::RenderWindow& w, Shader& shader) override
        {
            const float scale = WindowManager::get_scale(world_manager.get_camera());
            sprite.setScale({scale,scale});
            ///////화면 좌표 구하는 거 entityManager 전역 함수로 돌리고, entityManager에서는 그걸 바탕으로 update_entity
            ///객체별로 들어있는 백터 삭제하고 화면 상에 보이는 청크기준+1확장 청크까지 업데이트하도록 하는 update 함수
            const auto scaled_tile_size = image_data.size(scale);
            const auto pixel_world_size = WindowManager::get_pixel_world_size(world_manager.get_camera());
            
            const auto camera_pos = world_manager.get_camera().get_pos();
            const auto world_origin_in_screen = WindowManager::get_pixel_world_origin(world_manager.get_camera());

            const auto world_size = world_manager.get_world().get_size();

            const tools::POSi start = tools::POSi(
                std::max(0, tools::CASTi(floor(camera_pos.x - pixel_world_size.x / 2.f))),
                std::max(0, tools::CASTi(floor(camera_pos.y - pixel_world_size.y / 2.f)))
            );
            const tools::POSi end = tools::POSi(
                std::min(tools::CASTi(world_size.c), tools::CASTi(ceil(camera_pos.x + pixel_world_size.x / 2.f))),
                std::min(tools::CASTi(world_size.r), tools::CASTi(ceil(camera_pos.y + pixel_world_size.y / 2.f)))
            );

            for (int r = start.r; r < end.r; ++r)
            {
                for (int c = start.c; c < end.c; ++c)
                {
                    const auto npos = tools::POSi(c, r);
                    const auto draw_pos = world_origin_in_screen + (tools::POSf(npos) * scaled_tile_size);
                    const auto tile_code = world_manager.get_world()[tools::POSs(npos)];

                    const auto test_tile_code = WorldImageData::CroppedImageName((((long long)r*c+3*c+c*c+r*7)^3721873)%3);
                    const int test_tile_height = world_manager.get_world().get_height(npos)+(r+c);
                    const int test_cam_height = world_manager.get_camera().get_curr_height(world_manager.get_world())+((int)camera_pos.r+(int)camera_pos.c);
                    
                    shader.set_brightness(Shader::get_brightness_by_height(test_cam_height,test_tile_height));
                    print_tile(w, shader, draw_pos, test_tile_code);
                }
            }
        }
};