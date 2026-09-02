#include "entityManager.hpp"
#include "game/keyManager/keyboardManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/fallenItem/fallenItem.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/tree.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/bush.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity/interactableEntity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include "main/windowManager/windowManager.hpp"
#include "tools/cast.hpp"
#include "tools/pos.hpp"
#include <memory>
#include <random>
#include <cmath>


EntityManager::EntityManager(const World& world, std::vector<std::unique_ptr<Entity>>&& entities)
    : chunks(
        std::ceil(world.get_size().r / tools::CASTf(Chunk::CHUNK_SIZE)),
        std::vector<Chunk>(std::ceil(world.get_size().c/tools::CASTf(Chunk::CHUNK_SIZE)))
    )
{
    available_entity_code = Entity::UNREGISTERED;

    for(auto& entity : entities)
        register_entity(std::move(entity));
}

Chunk& EntityManager::get_chunk(const tools::POSs& pos)
{
    return chunks.at(pos.r).at(pos.c);
}
const Chunk& EntityManager::get_chunk(const tools::POSs& pos) const
{
    return chunks.at(pos.r).at(pos.c);
}
tools::POSs EntityManager::get_chunks_size() const
{
    return tools::POSs(chunks.at(0).size(),chunks.size());
}

bool EntityManager::is_valid_chunk(const tools::POSi& chunk_pos) const
{
    return chunk_pos.r >= 0 && chunk_pos.r < chunks.size() && chunk_pos.c >= 0 && chunk_pos.c < chunks[0].size();
}

void EntityManager::register_entity(std::shared_ptr<Entity> entity)
{
    if(auto p = std::dynamic_pointer_cast<Player>(entity))
        if(player.lock())
            throw std::runtime_error("only one player can exist");
        
    if(entity->is_registered())
        throw std::runtime_error("entity is already registered");
    entity->set_entity_code(++available_entity_code);

    if(auto p = std::dynamic_pointer_cast<Player>(entity))
        player = p;
    const auto chunk_pos = get_chunk_pos(entity);
    get_chunk(chunk_pos).insert(std::move(entity));
}
 
void EntityManager::unregister_entity(const std::shared_ptr<const Entity>& entity)
{
    if(!entity->is_registered())
        throw std::runtime_error("entity is not registered");
    const auto chunk_pos = get_chunk_pos(entity);
    get_chunk(chunk_pos).erase(entity);
    if(auto p = std::dynamic_pointer_cast<const Player>(entity))
        if(player.lock() == p)
            player.reset();
}

void EntityManager::reregister_entity(const std::shared_ptr<Entity>& entity, const tools::POSf& next_pos)
{
    const auto chunk_pos = get_chunk_pos(entity);
    const auto next_chunk_pos = get_chunk_pos(next_pos);
    get_chunk(chunk_pos).erase(entity);
    get_chunk(next_chunk_pos).insert(entity);
    entity->set_pos(next_pos);
}

std::pair<tools::POSs,tools::POSs> EntityManager::get_update_chunk_range(const World& world, const Camera& camera) const
{
    const auto [start_world, end_world] = WindowManager::get_displayed_world_range(world, camera);
    const auto start_chunk = get_chunk_pos(start_world);
    const auto end_chunk = get_chunk_pos(end_world);

    auto start = tools::POSs(
        std::max(0, tools::CASTi(start_chunk.c) - UPDATE_CHUNK_DIAMETER),
        std::max(0, tools::CASTi(start_chunk.r) - UPDATE_CHUNK_DIAMETER));
    auto end = tools::POSs(
        std::min(tools::CASTi(chunks[0].size()), tools::CASTi(end_chunk.c) + UPDATE_CHUNK_DIAMETER + 1),
        std::min(tools::CASTi(chunks.size()), tools::CASTi(end_chunk.r) + UPDATE_CHUNK_DIAMETER + 1));
    
    return {start,end};
}

void EntityManager::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    const auto [start, end] = get_update_chunk_range(world_manager.get_world(), world_manager.get_camera());
    for (size_t r = start.r; r < end.r; ++r)
    {
        for (size_t c = start.c; c < end.c; ++c)
        {
            auto& chunk = chunks[r][c];
            for(size_t i = 0 ; i < chunk.get_dynamic_entities_size() ; i++)
            {
                auto entity_ptr = chunk.get_dynamic_entity_ptr(i);
                entity_ptr->update(window_manager, world_manager);

                if(auto creature = std::dynamic_pointer_cast<Creature>(entity_ptr))
                {
                    if(!creature->is_alive())
                        unregister_entity(entity_ptr);
                }
                if(auto moving_entity = std::dynamic_pointer_cast<MovingEntity>(entity_ptr))
                {
                    if(moving_entity->is_moving())
                    {
                        auto next_pos = moving_entity->get_next_pos();
                        if(moving_entity->is_moveable_to(world_manager.get_world(), next_pos))
                        {
                            if(test_collision(*moving_entity, next_pos, world_manager.get_world()))
                                moving_entity->stop();
                            else
                                reregister_entity(moving_entity, next_pos);
                        }
                        else
                            moving_entity->stop();
                    }
                }
                if(auto item = std::dynamic_pointer_cast<FallenItem>(entity_ptr))
                {
                    if(item->is_interacted())
                        unregister_entity(entity_ptr);
                }
            }
        }
    }
}

std::vector<std::shared_ptr<Entity>> EntityManager::find_collided_dynamic_entities(const Entity& entity, const World& world)
{
    std::vector<std::shared_ptr<Entity>> collided_entities;
    const tools::POSi chunk_pos = get_chunk_pos(entity.get_pos());

    tools::POSi chunks_size = get_chunks_size();
    const tools::POSs start = {
        tools::CASTs(std::max(0, chunk_pos.c - 1)),
        tools::CASTs(std::max(0, chunk_pos.r - 1))};
    const tools::POSs end = {
        tools::CASTs(std::min(chunk_pos.c + 1, chunks_size.c - 1)),
        tools::CASTs(std::min(chunk_pos.r + 1, chunks_size.r - 1))};

    for (size_t row = start.r; row <= end.r; ++row)
        for (size_t col = start.c; col <= end.c; ++col)
        {
            tools::POSs chunk_pos(col, row);
            auto& chunk = get_chunk(chunk_pos);
            
            auto condition = [&entity, &world](const Entity& object){
                if (object == entity)
                    return false;
                return entity.is_collided(object, world);
            };
            
            auto dynamic_entities = chunk.find_dynamic_entities(condition);
            collided_entities.insert(collided_entities.end(), dynamic_entities.begin(), dynamic_entities.end());
        } 
    
    return collided_entities;
}


bool EntityManager::test_collision(const Entity& entity, const World& world)
{
    const tools::POSi chunk_pos = get_chunk_pos(entity.get_pos());

    tools::POSi chunks_size = get_chunks_size();
    const tools::POSs start = {
        tools::CASTs(std::max(0, chunk_pos.c - 1)),
        tools::CASTs(std::max(0, chunk_pos.r - 1))};
    const tools::POSs end = {
        tools::CASTs(std::min(chunk_pos.c + 1, chunks_size.c - 1)),
        tools::CASTs(std::min(chunk_pos.r + 1, chunks_size.r - 1))};

    for (size_t row = start.r; row <= end.r; ++row)
        for (size_t col = start.c; col <= end.c; ++col)
        {
            const auto& chunk = get_chunk({col,row});
            
            for(size_t i = 0; i < chunk.get_static_entities_size(); ++i)
                if(entity.is_collided(chunk.get_static_entity(i),world))
                    return true;
            for(size_t i = 0; i < chunk.get_dynamic_entities_size(); ++i)
                if(entity.is_collided(chunk.get_dynamic_entity(i),world))
                    return true;
        } 
    
    return false;
}
bool EntityManager::test_collision(Entity& entity, const tools::POSf& pos, const World& world)
{
    auto prev_pos = entity.get_pos();
    entity.set_pos(pos);
    const bool is_collided = test_collision(entity, world);
    entity.set_pos(std::move(prev_pos));
    return is_collided;
}


void EntityManager::allot_player_keys(KeyboardManager& keyboard_Manager)
{
    keyboard_Manager.allot_key(sf::Keyboard::Key::W, [this](){player.lock()->move_up();});
    keyboard_Manager.allot_key(sf::Keyboard::Key::S, [this](){player.lock()->move_down();});
    keyboard_Manager.allot_key(sf::Keyboard::Key::A, [this](){player.lock()->move_left();});
    keyboard_Manager.allot_key(sf::Keyboard::Key::D, [this](){player.lock()->move_right();});
}

Player& EntityManager::get_player() {return *player.lock();}
const Player& EntityManager::get_player() const {return *player.lock();}
std::shared_ptr<Player> EntityManager::get_player_ptr(){return player.lock();}
std::shared_ptr<const Player> EntityManager::get_player_ptr() const{return player.lock();}

void EntityManager::rebind_player()
{
    player.reset();
    for (auto& row : chunks)
        for (auto& chunk : row)
            for (size_t i = 0; i < chunk.get_dynamic_entities_size(); ++i)
                if (auto p = std::dynamic_pointer_cast<Player>(chunk.get_dynamic_entity_ptr(i)))
                {
                    player = p;
                    return;
                }
}

void EntityManager::generate_initial_entities(const World& world)
{
    if (player.lock())
        return;

    tools::POSs world_size = world.get_size();
    if (world_size.c == 0 || world_size.r == 0)
        return;

    tools::POSf center(world_size.c / 2.0f, world_size.r / 2.0f);

    // 1. 플레이어 위치: 섬 중앙부 근처의 잔디(GRASS) 타일 탐색
    tools::POSf player_pos = center;
    bool found_grass = false;
    for (int radius = 0; radius < (int)std::max(world_size.c, world_size.r) && !found_grass; ++radius)
    {
        for (int dr = -radius; dr <= radius && !found_grass; ++dr)
        {
            for (int dc = -radius; dc <= radius && !found_grass; ++dc)
            {
                int r = (int)center.y + dr;
                int c = (int)center.x + dc;
                if (r >= 0 && r < (int)world_size.r && c >= 0 && c < (int)world_size.c)
                {
                    if (world[tools::POSs(c, r)].name == Tile::TileName::GRASS)
                    {
                        player_pos = tools::POSf(c + 0.5f, r + 0.5f);
                        found_grass = true;
                    }
                }
            }
        }
    }

    register_entity(std::make_shared<Player>(player_pos));

    // 2. 맵 전체 잔디(GRASS) 타일 위치에 나무 자동 생성
    std::mt19937 rng(42);
    std::uniform_real_distribution<float> offset_dist(-0.35f, 0.35f);
    std::uniform_real_distribution<float> prob_dist(0.0f, 1.0f);

    std::vector<tools::POSf> tree_positions;
    const float STEP = 3.5f;

    for (float r = 1.5f; r < (float)world_size.r - 1.5f; r += STEP)
    {
        for (float c = 1.5f; c < (float)world_size.c - 1.5f; c += STEP)
        {
            float tile_c = c + offset_dist(rng);
            float tile_r = r + offset_dist(rng);
            tools::POSs grid_pos((size_t)tile_c, (size_t)tile_r);

            if (grid_pos.c >= world_size.c || grid_pos.r >= world_size.r)
                continue;

            // 잔디 타일 위에서만 생성
            if (world[grid_pos].name != Tile::TileName::GRASS)
                continue;

            tools::POSf pos(tile_c, tile_r);

            // 플레이어 주변 스폰 방지 (최소 2.5 거리)
            tools::POSf dplayer = pos - player_pos;
            if (dplayer.square_size() < 6.25f)
                continue;

            // 기존 나무 간격 유지 (최소 2.0 거리)
            bool too_close = false;
            for (const auto& existing_pos : tree_positions)
            {
                tools::POSf dtree = pos - existing_pos;
                if (dtree.square_size() < 4.0f)
                {
                    too_close = true;
                    break;
                }
            }
            if (too_close)
                continue;

            // 지역별 유사 나무 종류 배치 (중앙부는 TREE1, TREE2 / 외곽은 사방위별 TREE 종류 매핑)
            tools::POSf dcenter = pos - center;
            float dist_from_center = std::sqrt(dcenter.square_size());
            float max_radius = std::min(world_size.c, world_size.r) * 0.5f;

            Tree::TreeName tree_name = Tree::TreeName::TREE1;

            if (dist_from_center < max_radius * 0.35f)
            {
                // 섬 중앙 영역: 비슷 계열 (TREE1, TREE2)
                tree_name = (prob_dist(rng) < 0.6f) ? Tree::TreeName::TREE1 : Tree::TreeName::TREE2;
            }
            else
            {
                // 외곽 영역: 방위에 따라 비슷한 계열 묶음 지정
                float angle = std::atan2(dcenter.y, dcenter.x);
                if (angle < -1.57f)
                    tree_name = (prob_dist(rng) < 0.7f) ? Tree::TreeName::TREE3 : Tree::TreeName::TREE4;
                else if (angle < 0.0f)
                    tree_name = (prob_dist(rng) < 0.7f) ? Tree::TreeName::TREE4 : Tree::TreeName::TREE5;
                else if (angle < 1.57f)
                    tree_name = (prob_dist(rng) < 0.7f) ? Tree::TreeName::TREE6 : Tree::TreeName::TREE5;
                else
                    tree_name = (prob_dist(rng) < 0.7f) ? Tree::TreeName::TREE7 : Tree::TreeName::TREE6;
            }

            if (prob_dist(rng) < 0.75f)
            {
                register_entity(std::make_shared<Tree>(pos, 1.0f, tree_name));
                tree_positions.push_back(pos);

                if (prob_dist(rng) < 0.15f)
                {
                    tools::POSf item_pos = pos + tools::POSf(offset_dist(rng), offset_dist(rng));
                    register_entity(std::make_shared<FallenItem>(item_pos, FallenItem::ItemName::apple));
                }

                // 나무 주변에 낮은 확률로 bush 생성 (30% 확률, 1~2개)
                if (prob_dist(rng) < 0.30f)
                {
                    std::uniform_real_distribution<float> bush_angle_dist(0.0f, 6.2832f); // 0~2π
                    std::uniform_real_distribution<float> bush_radius_dist(1.1f, 2.4f);
                    int bush_count = (prob_dist(rng) < 0.4f) ? 2 : 1;
                    for (int bi = 0; bi < bush_count; ++bi)
                    {
                        float angle = bush_angle_dist(rng);
                        float radius = bush_radius_dist(rng);
                        tools::POSf bush_pos = pos + tools::POSf(std::cos(angle) * radius, std::sin(angle) * radius);

                        // 월드 경계 및 잔디 타일 체크
                        tools::POSs bush_grid((size_t)bush_pos.x, (size_t)bush_pos.y);
                        if (bush_grid.c >= world_size.c || bush_grid.r >= world_size.r)
                            continue;
                        if (world[bush_grid].name != Tile::TileName::GRASS)
                            continue;

                        // 플레이어 근처 스폰 방지
                        tools::POSf dp = bush_pos - player_pos;
                        if (dp.square_size() < 6.25f)
                            continue;

                        Bush::BushName bush_name = (prob_dist(rng) < 0.5f)
                            ? Bush::BushName::BUSH1
                            : Bush::BushName::BUSH2;
                        register_entity(std::make_shared<Bush>(bush_pos, 1.0f, bush_name));
                    }
                }
            }
        }
    }
}



