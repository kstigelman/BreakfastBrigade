#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"

class SplashScreen : public Screen {
private:
    sf::Clock timer;
    sf::Texture splashTexture;
    sf::Sprite splashSprite;

    int currentAlpha = 0;
public:
    SplashScreen () : Screen ("Splash", nullptr) {
        splashTexture.loadFromFile ("resources/sprites/Splash.png");
        splashSprite.setTexture (splashTexture);
        splashSprite.setScale (2, 2);
        splashSprite.setColor (sf::Color::Transparent);


        timer.restart ();
    }
    void update (float dt) override {
        float elapsedTime = timer.getElapsedTime ().asSeconds ();
            float offset;
            if (elapsedTime > 1 && elapsedTime < 2.5) {
                offset = 1;
                currentAlpha = std::clamp<float>((elapsedTime - offset) * (255 / 1.5), 0.f, 255.f);
                splashSprite.setColor (sf::Color (255, 255, 255, currentAlpha));
            }
            else if (elapsedTime > 5 && elapsedTime < 6.5) {
                offset = 5;
                currentAlpha = std::clamp<float>(100 - (elapsedTime - offset) * (255 / 1.5), 0.f, 255.f);
                splashSprite.setColor (sf::Color (255, 255, 255, currentAlpha));
            }
            else if (elapsedTime > 9) {
               setScreenFinished (true);
            }
    }
    void draw (sf::RenderWindow& window) override {
        window.draw (splashSprite);
    }


};