#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Window
{
    private:
        sf::Vector2i size;
        sf::RenderWindow window;
    public:
        Window (std::string title = "New window", int width = 1280, int height = 720) {
            size = sf::Vector2i (width, height);
            window.create(title, sf::VideoMode(width, height));
            window.setFramerateLimit (60);
        }
        sf::RenderWindow& getSize () {
            return size;
        }
        void setFramerate (int fps) {
            window.setFramerateLimit (fps);
        }
        bool resize (sf::Vector2i newSize) {
            size = newSize;
            window.setSize (size);
        }
        void rescale () {
            
        }

}
