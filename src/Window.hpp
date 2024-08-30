#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Window
{
    private:
        sf::Vector2i m_size;
        sf::RenderWindow m_window;
        std::string m_title;
    public:
        Window (std::string title = "New window", int width = 1280, int height = 720) {
            m_title = title;
            m_size = sf::Vector2i (width, height);
            m_window.create(title, sf::VideoMode(width, height));
            m_window.setFramerateLimit (60);
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
        void
        draw (sf::Drawable drawable) {
            m_window.draw (sprite);
        }
        
}
