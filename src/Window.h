#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>

class Window
{
    private:
        sf::Vector2i size;
        sf::RenderWindow window;
    public:
        Window::Window (std::string title = "New window", int width = 1280, int height = 720);
        sf::RenderWindow& GetWindow ();
        void setFramerate (int fps);
        bool resize (sf::Vector2i newSize);
        sf::Vector2i getSize ();
}
#endif