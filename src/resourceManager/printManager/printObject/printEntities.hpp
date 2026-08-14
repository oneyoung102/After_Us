#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/fallenItem/fallenItem.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/tree.hpp"
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
        
        inline tools::POSi get_tex_pos(const Entity& entity, const ImageDatas::IMAGE_DATA& image_data)
        {
            if (auto creature = dynamic_cast<const Creature*>(&entity))
                return image_data[creature->get_moving_state()];
            else if (auto item = dynamic_cast<const FallenItem*>(&entity))
                return image_data[item->get_item_name()];
            else if (auto thing = dynamic_cast<const Thing*>(&entity))
            {
                if (auto tree = dynamic_cast<const Tree*>(thing))
                    return image_data[tree->get_tree_name()];
                else if (auto bush = dynamic_cast<const Bush*>(thing))
                    return image_data[bush->get_bush_name()];
            }

            return {0, 0};
        }
        
        void print_entity(sf::RenderWindow& w, Shader& shader, const tools::POSf& screen_pos, const Entity& entity)
        {
            shader.set_brightness(shader.get_brightness_by_height(world[entity.get_pos()].height, world[camera.get_target_pos()].height));
            
            const auto& image_data = image_datas[entity.get_name()];
            const auto tex_size = image_data.size();
            const auto entity_size = entity.get_size();

            sf::Sprite sprite = image_data.get_sprite();
            sprite.setScale({entity_size*scale, entity_size*scale});

            sprite.setOrigin({tex_size.x / 2.f, tools::CASTf(tex_size.y)}); 

            const auto tex_pos = get_tex_pos(entity, image_data);
            sprite.setTextureRect(sf::IntRect({tex_pos.x, tex_pos.y}, {tex_size.x, tex_size.y}));

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
                std::vector<std::shared_ptr<const Entity>> entity_queue;
                for (size_t c = start_chunk.c; c < end_chunk.c; ++c)
                {
                    const auto& chunk = entity_manager.get_chunk({c, r});
                    const int static_size = chunk.get_static_entities_size();
                    for(size_t i = 0; i < static_size; ++i)
                        entity_queue.push_back(chunk.get_static_entity_ptr(i));
                    const int dynamic_size = chunk.get_dynamic_entities_size();
                    for(size_t i = 0; i < dynamic_size; ++i)
                        entity_queue.push_back(chunk.get_dynamic_entity_ptr(i));
                    
                    
                }
                std::sort(entity_queue.begin(), entity_queue.end(), [](const auto& a, const auto& b){
                        if(!a) return true;
                        if(!b) return false;
                        return a->get_pos().y < b->get_pos().y;
                    });
                for(const auto& entity : entity_queue)
                {
                    if(!entity) continue;
                    print_entity(w, shader, WindowManager::world_pos_to_pixel_pos(entity->get_pos(), camera), *entity);
                }
            }
            
            if(is_alive())
                --life;
        }
};