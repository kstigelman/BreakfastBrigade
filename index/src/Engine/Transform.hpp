#pragma once
#include <SFML/Graphics.hpp>

struct Transform {
    sf::Vector2f position = sf::Vector2f (0.0, 0.0);
    float rotation = 0.0;
    sf::Vector2f scale = sf::Vector2f (1.0, 1.0);

    sf::Vector2f velocity = sf::Vector2f (0.0, 0.0);
};