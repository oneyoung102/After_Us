#pragma once

#include "tools/tick.hpp"
#include <SFML/Graphics.hpp>

#include <optional>
#include <functional>
#include <array>

class KeyboardManager
{
    private :
        static constexpr size_t KEY_MAX_AMOUNT = 101;
        std::array<std::function<void()>, KEY_MAX_AMOUNT> key_allot;
        std::array<tools::Tick, KEY_MAX_AMOUNT> key_delay;
        std::array<tools::Tick, KEY_MAX_AMOUNT> remained_key_delay;

        bool is_valid_key(sf::Keyboard::Key key) const;
    public :
        KeyboardManager();
        void update(const std::optional<sf::Event>& event);
        void act_key_event();
        void allot_key(sf::Keyboard::Key key, std::function<void()>&& func, tools::Tick delay = 0);
        void clear();
        void clear(sf::Keyboard::Key key);
};
#define FUNCFY(x) [this](){return x();}