#pragma once

#include "game/keyManager/pointer/pointer.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/player.hpp"
#include "tools/pos.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <functional>


class MouseManager
{
    private :
        Pointer pointer;

        constexpr static size_t KEY_MAX_AMOUNT = 5;
        std::array<std::function<void()>,KEY_MAX_AMOUNT> key_allot;
        std::array<tools::Tick, KEY_MAX_AMOUNT> key_delay;
        std::array<tools::Tick, KEY_MAX_AMOUNT> remained_key_delay;

        bool is_valid_key(sf::Mouse::Button key) const;
    public :
        MouseManager();
        void show_mouse_cursor(sf::Window& window, bool show);
        tools::POSf get_mouse_pos(const WindowManager& window_manager) const;
        void anchor_mouse(const WindowManager& window_manager, const Camera& camera, const Player& player);

        void update();
        void act_key_event();
        void allot_key(sf::Mouse::Button key, std::function<void()>&& func, tools::Tick delay = 0);
        void clear();
        void clear(sf::Mouse::Button key);

        const Pointer& get_pointer() const;
        Pointer& get_pointer();
};