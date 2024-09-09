#pragma once
#include <SFML/Graphics.hpp>

#include "Animator.hpp"


class Ship {
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        Animator animator;

        float elapsedTime = 0;

        float basePos = 360;
    public:
        Ship () {
            m_texture.loadFromFile ("resources/sprites/ship-Sheet.png");
            m_sprite.setTexture (m_texture);
            m_sprite.setScale (4, 4);
            m_sprite.setPosition (360, 360);
            m_sprite.setOrigin (15, 6);
            animator = Animator (m_texture, &m_sprite, 7, 7);

        }

        void update (float dt) {
            animator.nextFrame ();
            elapsedTime += dt;
            m_sprite.setPosition (360, basePos + (15 * std::sin (elapsedTime * 3.6 / 3.14)));
        }
        void draw (sf::RenderWindow& window) {
            animator.draw(window);
        }

};