#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "../UI/Animator.hpp"

class Ship : public Entity {
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        Animator animator;

        float elapsedTime = 0;

        float basePos = 360;

        bool destroyed = true;
        Collider interactZone;

        HealthBar healthbar;
    public:
        Ship (Level* world) : Entity (world, sf::RectangleShape (sf::Vector2f (30, 15))) {
            texture.loadFromFile ("resources/sprites/destroyed_ship.png");
            sprite.setTexture (texture);
            sprite.setScale (2, 2);
            sprite.setPosition (360, 360);
            collider.setPosition (sprite.getPosition());
            //m_sprite.setOrigin (15, 6);
            animator = Animator (texture, &sprite, 3, 4);
            healthbar = HealthBar (100, sf::Vector2f (60, 6));

            interactZone = Collider (100, 100);
        }

        void setDestroyed (bool newVal) {
            destroyed = newVal;
            if (newVal) {
                texture.loadFromFile ("resources/sprites/destroyed_ship.png");
                sprite.setTexture (texture);
                sprite.setScale (3, 3);
                sprite.setPosition (360, 360);
                sprite.setOrigin (15, 6);
                animator = Animator (texture, &sprite, 3, 4);
                
            }
            else {
                texture.loadFromFile ("resources/sprites/ship.png");
                sprite.setTexture (texture);
                sprite.setScale (4, 4);
                sprite.setPosition (360, 360);
                sprite.setOrigin (15, 6);
                animator = Animator (texture, &sprite, 7, 7);
            }

        }
        virtual void update (float dt) {
            Entity::update (dt);
            //collider.setPosition (m_sprite.getPosition());
            healthbar.setPosition (sprite.getPosition() + sf::Vector2f (0, -30));

            if (!destroyed) {
                animator.nextFrame ();
                elapsedTime += dt;
                sprite.setPosition (360, basePos + (15 * std::sin (elapsedTime * 3.6 / 3.14)));
            }
            if (destroyed) {
                animator.nextFrame ();
            }
        }
        virtual void damage (sf::Vector2f source, int amount) {
            healthbar.takeDamage (amount);
        }
        void draw (sf::RenderWindow& window) {
            animator.draw (window);
            healthbar.draw (window);
        }
        Collider getInteractionZone () {
            return interactZone;
        }
};