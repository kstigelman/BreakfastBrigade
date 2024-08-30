#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>

#include "Window.hpp"

class Application
{
    protected:
        std::string m_name;

        Window m_window;

    public:
    Application (std::string name = "New application") {
        m_name = name;
        m_window = Window(name);
    }


    Window
    getWindow () {
        return m_window;
    }
    virtual void
    run () {
        eventHandler ();
        update ();
    }

    std::string getName () {
        return name;
    }

    Window
    getWindow () {
        return m_window;
    }
    void
    eventHandler () {
        
    }

    void 
    update () {

    }


};