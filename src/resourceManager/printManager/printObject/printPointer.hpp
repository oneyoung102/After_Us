#pragma once

#include "resourceManager/printManager/printObject/printObject.hpp"
#include <SFML/Graphics.hpp>
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include "game/keyManager/pointer/pointer.hpp"
#include "game/keyManager/mouseManager.hpp"
#include "tools/pos.hpp"

template<>
class PrintObject<Pointer> : public PrintObjectInterface
{
    private :
        float scale;
        const ImageDatas::IMAGE_DATA& pointer_image_data;
        const WorldManager& world_manager;
        const Camera& camera;
        const MouseManager& mouse_manager;
    public :
        PrintObject(const ImageDatas& image_datas, const WorldManager& world_manager, const MouseManager& mouse_manager)
            : PrintObjectInterface(image_datas)
            , pointer_image_data(image_datas[ImageDatas::Name::pointer])
            , world_manager(world_manager)
            , camera(world_manager.get_camera())
            , mouse_manager(mouse_manager)
        {}

        virtual void print(sf::RenderWindow& w, Shader& shader) override
        {
            auto player_ptr = world_manager.get_entity_manager().get_player_ptr();
            if (!player_ptr)
                return;

            const auto& pointer = mouse_manager.get_pointer();
            const auto scale = WindowManager::get_scale(camera)*pointer.get_size();
            
            const auto crop_name = pointer.is_focusing() ? PointerImageData::CroppedImageName::FOCUSING : PointerImageData::CroppedImageName::UNFOCUSING;
            const auto tex_pos = pointer_image_data[crop_name];
            const auto tex_size = pointer_image_data.size();

            sf::Sprite tile_sprite = pointer_image_data.get_sprite();
            tile_sprite.setScale({scale, scale});
            tile_sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {tex_size.x, tex_size.y}));
            tile_sprite.setOrigin({tex_size.x / 2.f, tex_size.y / 2.f});

            const tools::POSs draw_pos = WindowManager::world_pos_to_pixel_pos(pointer.get_pos(), camera);
            print_sprite(w,tile_sprite,draw_pos,shader);

            if(is_alive())
                --life;
        }
};