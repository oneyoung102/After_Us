#include "game/keyManager/mouseManager.hpp" 
#include "main/windowManager/windowManager.hpp"

MouseManager::MouseManager()
    : pointer()
{
    clear();
}

void MouseManager::show_mouse_cursor(sf::Window& window, bool show)
{
    window.setMouseCursorVisible(show);
}
tools::POSf MouseManager::get_mouse_pos(const WindowManager& window_manager) const
{
    const auto& window = window_manager.get_window();
    const auto& view = window_manager.get_view();
    sf::Vector2f view_pos = window.mapPixelToCoords(sf::Mouse::getPosition() - window.getPosition(), view);
    return {view_pos.x, view_pos.y};
}
void MouseManager::anchor_mouse(const WindowManager& window_manager, const Camera& camera, const Player& player)
{
    const auto& window = window_manager.get_window();
    const auto& view = window_manager.get_view();

    tools::POSf world_pos = WindowManager::pixel_pos_to_world_pos(get_mouse_pos(window_manager), camera);
    tools::POSf anchor_pos = player.get_pos() + tools::POSf(0, -0.375f);
    tools::POSf diff = world_pos - anchor_pos;
    float dist = sqrt(diff.square_size());
    float reach = player.get_reach();
    
    if (dist > reach)
    {
        world_pos = anchor_pos + diff * (reach / dist);
        tools::POSf screen_pos = WindowManager::world_pos_to_pixel_pos(world_pos, camera);
        sf::Mouse::setPosition(window.getPosition() + window.mapCoordsToPixel({screen_pos.x, screen_pos.y}, view));
    }
    pointer.set_pos(world_pos);
}

bool MouseManager::is_valid_key(sf::Mouse::Button key) const
{
    int val = static_cast<int>(key);
    return 0 <= val && val < KEY_MAX_AMOUNT;
}

void MouseManager::update()
{
    bool clicked = false;
    for(size_t i = 0 ; i < KEY_MAX_AMOUNT ; ++i)
    {
        const auto key = static_cast<sf::Mouse::Button>(i);
        if(is_valid_key(key))
        {
            if(sf::Mouse::isButtonPressed(key))
            {
                remained_key_delay[i] = key_delay[i];
                clicked = true;
            }
            else if(remained_key_delay[i] >= 0)
                --remained_key_delay[i];
        }
    }
    pointer.focus(clicked);
}
void MouseManager::act_key_event()
{ 
    for(size_t i = 0; i < key_allot.size(); ++i)
        if(key_allot[i] && remained_key_delay[i] == key_delay[i])
            key_allot[i]();
}
void MouseManager::allot_key(sf::Mouse::Button key, std::function<void()>&& func, tools::Tick delay)
{
    if(is_valid_key(key))
    {
        key_allot[static_cast<size_t>(key)] = std::move(func);
        key_delay[static_cast<size_t>(key)] = delay;
        remained_key_delay[static_cast<size_t>(key)] = -1;
    }
}
void MouseManager::clear()
{
    key_allot.fill(nullptr);
    remained_key_delay.fill(0);
    key_delay.fill(-1);
}
void MouseManager::clear(sf::Mouse::Button key)
{
    if(is_valid_key(key))
    {
        key_allot[static_cast<size_t>(key)] = nullptr;
        key_delay[static_cast<size_t>(key)] = -1;
        remained_key_delay[static_cast<size_t>(key)] = -1;
    }
}

const Pointer& MouseManager::get_pointer() const {return pointer;}
Pointer& MouseManager::get_pointer() {return pointer;}