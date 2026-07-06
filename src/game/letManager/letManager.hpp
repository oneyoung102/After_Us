#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <functional>
#include <array>

class LetManager
{
    private :
        static constexpr size_t KEY_MAX_AMOUNT = 101;
        std::array<std::function<void()>, KEY_MAX_AMOUNT> state_key_allot;
        std::array<std::function<void()>, KEY_MAX_AMOUNT> event_key_allot;
        std::array<bool, KEY_MAX_AMOUNT> state_keys_pressed;

        bool is_valid_key(sf::Keyboard::Key key) const;
    public :
        LetManager();
        void act_event_let(const std::optional<sf::Event>& event);
        void act_state_let();
        void allot_state_key(sf::Keyboard::Key key, std::function<void()>&& func);
        void allot_event_key(sf::Keyboard::Key key, std::function<void()>&& func);
        void clear();
        void clear(sf::Keyboard::Key key);
};
#define FUNCFY(x) [this](){return x();}