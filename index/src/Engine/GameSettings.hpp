#pragma once
#include <SFML/Graphics.hpp>

struct GameSettings {
    std::string applicationName = "The Breakfast Brigade";
    unsigned WIDTH = 576;
    unsigned HEIGHT = 720;

    sf::Vector2i mouseCoords = sf::Vector2i (0.0, 0.0);
    class Scene* currentScene;
    bool bLeftClicked = false;
};