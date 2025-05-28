#pragma once
#include "ButtonRegistry.hpp"

class Button;

class UIRegistry {
    private:
        ButtonRegistry* buttonRegister;
    public:
        UIRegistry () {

        }
        void add (UIElement* element) {
            if (element->getType () == "Button")
                buttonRegister->addButton ((Button*) element);
        }

        void update (float dt) {
            buttonRegister->update (dt);
        }
        void eventHandler (sf::Event& e) {
            buttonRegister->eventHandler (e);
        }
        void draw (sf::RenderWindow& window) {
            buttonRegister->draw (window);
        }


        
};