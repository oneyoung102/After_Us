#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/fallenItem/fallenItem.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

#include "main/windowManager/windowManager.hpp"
#include "resourceManager/printManager/printObject/printObject.hpp"
#include "resourceManager/printManager/shader/shader.hpp"
#include "tools/cast.hpp"
#include "tools/pos.hpp"
#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include <SFML/Graphics.hpp>


template<>
class PrintObject<Entity> : public PrintObjectInterface
{
    private :
        float scale;
        const World& world;
        const Camera& camera;
        const EntityManager& entity_manager;
        std::vector<sf::Sprite> entity_sprites;
        
        
        void print_entity(sf::RenderWindow& w, Shader& shader, const tools::POSf& screen_pos, const Entity& entity)
        {
            shader.set_brightness(shader.get_brightness_by_height(world.get_height(entity.get_pos()), world.get_height(camera.get_target_pos())));
            
            const auto& image_data = image_datas[entity.get_name()];
            const auto tex_size = image_data.size();
            const auto entity_size = entity.get_size();

            sf::Sprite sprite = image_data.get_sprite();
            sprite.setScale({entity_size*scale, entity_size*scale});

            sprite.setOrigin({tex_size.x / 2.f, tools::CASTf(tex_size.y)}); 

            if(auto creature = dynamic_cast<const Creature*>(&entity))
            {
                const auto tex_pos = image_data[creature->get_moving_state()];
                sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {tex_size.x, tex_size.y}));
            }
            else if(auto item = dynamic_cast<const FallenItem*>(&entity))
            {
                const auto tex_pos = image_data[item->get_item_name()];
                sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {tex_size.x, tex_size.y}));       
            }
            else
            {

            }
            print_sprite(w,sprite,screen_pos,shader);
        }
        
    public :
        PrintObject(const ImageDatas& image_datas, const WorldManager& world_manager)
            : PrintObjectInterface(image_datas)
            , scale(0)
            , world(world_manager.get_world())
            , camera(world_manager.get_camera())
            , entity_manager(world_manager.get_entity_manager())
        {}

        virtual void print(sf::RenderWindow& w, Shader& shader) override
        {
            scale = WindowManager::get_scale(camera);
            
            const auto [start_chunk, end_chunk] = entity_manager.get_update_chunk_range(world, camera);
            const auto [start, end] = WindowManager::get_displayed_world_range(world,camera);
            const auto world_origin_in_screen = WindowManager::get_pixel_world_origin(camera);

            for (size_t r = start_chunk.r; r < end_chunk.r; ++r)
            {
                for (size_t c = start_chunk.c; c < end_chunk.c; ++c)
                {
                    auto& chunk = entity_manager.get_chunk({c, r});

                    int static_idx = 0, dynamic_idx = 0;
                    const int static_size = chunk.get_static_entities_size();
                    const int dynamic_size = chunk.get_dynamic_entities_size();

                    while(static_idx < static_size || dynamic_idx < dynamic_size)
                        if(static_idx < static_size && (dynamic_idx >= dynamic_size || chunk.get_static_entity(static_idx).get_pos().y < chunk.get_dynamic_entity(dynamic_idx).get_pos().y))
                        {
                            const auto& static_entity = chunk.get_static_entity(static_idx);
                            const auto static_pos = static_entity.get_pos();
                            if(start <= static_pos && static_pos < end)
                                print_entity(w, shader, WindowManager::world_pos_to_pixel_pos(static_pos, camera), static_entity);
                            ++static_idx;
                        }
                        else
                        {
                            const auto& dynamic_entity = chunk.get_dynamic_entity(dynamic_idx);
                            const auto dynamic_pos = dynamic_entity.get_pos();
                            if(start <= dynamic_pos && dynamic_pos < end)
                                print_entity(w, shader, WindowManager::world_pos_to_pixel_pos(dynamic_pos, camera), dynamic_entity);
                            ++dynamic_idx;
                        }
                }
            }
            if(is_alive())
                --life;
        }
};