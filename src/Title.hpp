#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AnimatedObject.hpp"
#include <algorithm>
class Title {
public:
    enum Phase {
        SPLASH,
        TITLE,
        SELECT,
        SETTINGS,
        SCORES
    };
    sf::Texture backgroundTexture;
    sf::Sprite background[2];

    sf::Texture splashTexture;
    sf::Sprite splashSprite;

    sf::Texture title;
    sf::Sprite titleSprite;

    AnimatedObject ship = AnimatedObject ("resources/sprites/ship.png", 7, 7); 
    

    Phase currentPhase;
    //sf::SoundBuffer soundBuffer;
    //sf::Music theme;
    sf::Clock timer;

    int currentAlpha = 0;
    int fadePhase = 0;
    
    
    Title () {
        
        splashTexture.loadFromFile ("resources/sprites/Splash.png");
        splashSprite.setTexture (splashTexture);
        splashSprite.setScale (2, 2);


        splashSprite.setColor (sf::Color::Transparent);
        backgroundTexture.loadFromFile ("resources/sprites/Night.png");
        background[0].setTexture (backgroundTexture);
        background[1].setTexture (backgroundTexture);
        background[0].setScale (10, 10);
        background[1].setScale (10, 10);

        title.loadFromFile ("resources/sprites/title.png");
        titleSprite.setTexture (title);
        titleSprite.setOrigin (23, 9);
        titleSprite.setPosition (360, -100);
        titleSprite.setScale (8, 8);
        
        //background[1].setPosition (1000, 0);
        currentPhase = SPLASH;


        //soundBuffer.loadFromFile ("resources/audio/Theme.wav");

        /*theme.openFromFile ("resources/audio/Theme.wav");
        theme.setLoopPoints (sf::Music::TimeSpan (sf::milliseconds (17600), sf::milliseconds (33270)));
        theme.setLoop (true);
        theme.play();*/
        timer.restart ();

        ship.getSprite().setScale (4, 4);
        ship.getSprite().setPosition (360, 360);
        ship.getSprite().setOrigin (15, 6);
    }
    void update (float dt) {
        if (currentPhase == SPLASH) {
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
                currentPhase = TITLE;
            } 
        }
        else if (currentPhase == TITLE) {
            ship.update (dt, [this](float dt){
                ship.setPosition (360, 360 + (15 * std::sin (ship.elapsedTime * 3.6 / 3.14)));
            });
            for (int i = 0; i < 2; ++i) {
                if (background[i].getPosition ().x < -1000) {
                    background[i].setPosition (0, 0);
                }
                background[i].move (-dt * 500, 0);
            }
            if (titleSprite.getPosition().y < 180) {
                titleSprite.move (0, dt * 100);
            }
            else {
                titleSprite.setPosition (360, 180);
            }
            

        }
    }
    void draw (sf::RenderWindow& window) {
        if (currentPhase == SPLASH) {
            window.draw (splashSprite);
        }
        else if (currentPhase == TITLE) {
            window.draw (background[0]);
            window.draw (background[1]);
            ship.draw (window);
            window.draw (titleSprite);
        }
    }

};