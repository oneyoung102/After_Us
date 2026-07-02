#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <functional>
#include <array>

class LetManager
{
    private :
        std::array<std::function<void()>, 101> key_allot;
    public :
        LetManager();
        void act_keyboard_let(const std::optional<sf::Event>& event);
        void allot_key(sf::Keyboard::Key key, std::function<void()>&& func);
        void clear();
        void clear(sf::Keyboard::Key key);
};
#define FUNCFY(x) [this](){return x();}