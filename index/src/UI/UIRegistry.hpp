#pragma once

#include "UIElement.hpp"
#include "../Engine/GameSettings.hpp"

class UIRegistry {
    private:
        std::vector<UIElement*> elements;
        GameSettings* gameSettings;
    public:
        UIRegistry (GameSettings* gameSettings) : gameSettings(gameSettings) {

        }
        ~UIRegistry () {
            elements.clear();
        }
        GameSettings* getSettings() {
            return gameSettings;
        }
        void add (UIElement* element) {
            elements.push_back (element);

            //if (element->getType () == "Button") {}
            
        }
        void clear () {
            elements.clear();
        }
        void remove (int index) {
            int end = elements.size() - 1;
            UIElement* temp = elements[end];
            elements[end] = elements[index];
            elements[index] = temp;
        }
    
        std::vector<UIElement*>& getElements () {
            return elements;
        }
        void draw (sf::RenderWindow& window) {
            for (size_t index = 0; index < elements.size(); ++index) {
                if (!elements[index]->isVisible ())
                    continue;
                
                elements[index]->draw (window);
            }
        }
        void update (float dt) {
            for (size_t index = 0; index < elements.size(); ++index) {
                if (!elements[index]->shouldUpdate ())
                    continue;

                elements[index]->update (dt);
            }
            
        }
        void eventHandler (sf::Event& e) {
            for (size_t index = 0; index < elements.size(); ++index)
                elements[index]->eventHandler (e);
        }
        
};