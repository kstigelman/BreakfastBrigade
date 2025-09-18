#pragma once
#include <vector>
#include "Button.hpp"

class ButtonRegistry {
private:
    std::vector<Button*> buttons;

public:
    ButtonRegistry () {

    }
    void addButton (UIElement* button) {

        buttons.push_back ((Button*) button);
    }
    void removeButton (int index) {
        int end = buttons.size() - 1;
        Button* temp = buttons[end];
        buttons[end] = buttons[index];
        buttons[index] = temp;
    }
    std::vector<Button*>& getButtons () {
        return buttons;
    }
    void draw (sf::RenderWindow& window) {
        for (size_t index = 0; index < buttons.size(); ++index) {
            if (!buttons[index]->isVisible ())
                continue;
            
            buttons[index]->draw (window);
        }
    }
    void update (float dt) {
        for (size_t index = 0; index < buttons.size(); ++index) {
            if (!buttons[index]->shouldUpdate ())
                continue;

            buttons[index]->update (dt);
                
        }
        
    }
    void eventHandler (sf::Event& e) {
        if (e.type == sf::Event::MouseMoved) {
            for (size_t index = 0; index < buttons.size(); ++index) {
                if (!buttons[index]->shouldUpdate ())
                    continue;

                if (buttons[index]->contains (sf::Vector2f (e.mouseMove.x, e.mouseMove.y)))
                    buttons[index]->onHovered ();
            }
        }
        if (e.type == sf::Event::MouseButtonPressed) {
            for (size_t index = 0; index < buttons.size(); ++index) {
                if (!buttons[index]->shouldUpdate ())
                    continue;

                if (e.mouseButton.button == sf::Mouse::Left)
                    buttons[index]->onClicked ();  
            }
        }
    }
};