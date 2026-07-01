#pragma once

#include <SFML/Graphics.hpp>

const sf::Event::Resized* getResizeEvent(const sf::Event& event);
sf::FloatRect windowResize(const sf::Event::Resized* resize, float RATIO);
