#include <iostream>
#include <SFML/Graphics.hpp>

#include "Window.h"


Window::Window (std::string title = "New window", int width = 1280, int height = 720) {
    size = sf::Vector2i (width, height);
    window.create(title, sf::VideoMode(width, height));
    window.setFramerateLimit (60);
}
sf::RenderWindow& Window::GetWindow () {
    return window;
}
void Window::setFramerate (int fps) {
    window.setFramerateLimit (fps);
}
bool Window::resize (sf::Vector2i newSize) {
    size = newSize;
    window.setSize (size);
}
sf::Vector2i Window::getSize () {
    return size;
}