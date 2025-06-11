#pragma once
#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "Animator.hpp"
#include "UIRegistry.hpp"

#include <functional>


class Button : public UIElement {
    private:
        typedef void (*Func)(float);
        sf::Vector2f size;
        sf::Texture texture;
        sf::Sprite background;
        

        std::function<void()> functionOnClick;

        bool bBackgroundSet = false;
        std::string label;
    public:
        Button (UIRegistry* registry, std::string label, sf::Vector2f position, sf::Vector2f size)
        : UIElement(registry->getSettings(), position, size), label(label)
        {   
            setType ("Button");
            setVisibility (true);
            //background.setTextureRect (sf::IntRect (0, 0, texture.getSize().x, texture.getSize().y / 2));   
            //background.setPosition (position);    

            registry->add (this);
        }
        
        bool isClicked () {
            if (!bClicked)
                return false;
            bClicked = false;
            functionOnClick();
            return true;
        }
        bool contains (sf::Vector2f position) {
            return getElement().contains(position);
        }

        void
        update (float dt) override {

        }
        void eventHandler (sf::Event& e) override {
            if (!bShouldUpdate)
                return;

            if (e.type == sf::Event::MouseMoved) {
                if (contains (sf::Vector2f (getSettings()->mouseCoords.x, getSettings()->mouseCoords.y))) {
                    onHovered ();
                }
                else
                    onNotHovered ();
            }
            
            if (sf::Mouse::isButtonPressed (sf::Mouse::Left) && contains (sf::Vector2f(getSettings()->mouseCoords.x, getSettings()->mouseCoords.y))) {
                onClicked ();
            }
        }
        
        void setPosition (sf::Vector2f newPosition) override {
            UIElement::setPosition (newPosition);
            background.setPosition (newPosition);
        }
        void 
        draw (sf::RenderWindow& window) override {
            if (!bBackgroundSet || !bVisible)
                return;
            
            window.draw (background);
        }
        void setImage (std::string file) {
            setImage (file, 1);
        }
        void setImage (std::string file, int scale) {
            if (!texture.loadFromFile (file))
                return;
            background.setTexture (texture);
            background.setTextureRect (sf::IntRect (0, 0, texture.getSize().x, texture.getSize().y / 2));
            setPosition (getPosition ());
            bBackgroundSet = true;
            background.setScale (scale, scale);
            sf::Vector2f currentSize = background.getGlobalBounds ().getSize();
            setSize (sf::Vector2f (currentSize.x, currentSize.y));
        }
        // By default, mirror over x-axis. Specify if Y axis
        void mirror (bool direction = 0) {
            if (direction)
                background.setScale (1.0, -1.0);
            else
                background.setScale (-1.0, 1.0);
        }
        void setColor (sf::Color color) {
            background.setColor (color);
        }
        void onHovered () {
            if (!bBackgroundSet)
                return;
            background.setTextureRect (sf::IntRect (0,  texture.getSize().y / 2, texture.getSize().x, texture.getSize().y / 2));  
            
        }
        void onNotHovered () {
            if (!bBackgroundSet)
                return;
            background.setTextureRect (sf::IntRect (0, 0, texture.getSize().x, texture.getSize().y / 2));  
        }
        void setOnClicked (std::function<void()> newFunc) {
            functionOnClick = newFunc;
            
        }
        void onClicked () {
            functionOnClick();
           
        }

        
};