#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h> 
#include <functional>

#include "Animator.hpp"

class AnimatedObject {
    private:
        typedef void (*Func)(float);

        sf::Texture texture;
        sf::Sprite sprite;
        Animator animator;

        
    public:
        float elapsedTime;
        AnimatedObject (std::string filepath, int frames, int fr) {
            texture.loadFromFile (filepath);
            sprite.setTexture (texture);
            animator = Animator (&sprite, frames, fr);
        }
        AnimatedObject (std::string filepath, int frames, int fr, void (*setup)()) {
            AnimatedObject (filepath, frames, fr);
            setup();
        }
        void update (float dt, std::function<void(float)> func) {
            animator.nextFrame ();
            elapsedTime += dt;
            func (dt);
        }
        void draw (sf::RenderWindow& window) {
            window.draw (sprite);
        }
        sf::Sprite& getSprite () {
            return sprite;
        }
        void setPosition (float x, float y) {
            sprite.setPosition (x, y);
        }
};