#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Window
{
    private:
        sf::Vector2u m_size;
        sf::RenderWindow m_window;
        std::string m_title;
    public:
        Window (std::string title = "New window", int width = 1280, int height = 720) {
            m_title = title;
            m_size = sf::Vector2u (width, height);
            m_window.create(sf::VideoMode(width, height), title);
            m_window.setFramerateLimit (60);
        }
        sf::Vector2u& getSize () {
            return m_size;
        }
        void setFramerate (int fps) {
            m_window.setFramerateLimit (fps);
        }
        bool resize (sf::Vector2u newSize) {
            m_size = newSize;
            m_window.setSize (m_size);
        }
        void rescale () {
            
        }
        void
        draw (sf::Drawable drawable) {
            m_window.draw (drawable);
        }
        
};
