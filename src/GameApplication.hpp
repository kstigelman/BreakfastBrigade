#pragma once
#include <SFML/Graphics.hpp>

#include "Application.hpp"

class GameApplication : public Application
{
    sf::RectangleShape shape(100);
    GameApplication () {

    }
    virtual void
    run () {
        m_window.draw (shape);
    }

}