

#pragma once
#include <SFML/Graphics.hpp>


class Button {
    private:
        sf::Vector2f size;
        sf::Sprite background;
        bool bVisible;
    public:
        bool isVisible () {
            return bVisible;
        }
        bool setVisibility (bool bNewVis) {
            bVisible = bNewVis;
        }
        virtual void OnClick ();

        void Draw () {

        }
        
};