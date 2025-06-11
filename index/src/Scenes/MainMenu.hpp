#pragma once
#include "Scene.hpp"
#include "../UI/AnimatedObject.hpp"
#include "../UI/Button.hpp"

#include "ColiforB.hpp"
#include "Screens/Screen.hpp"
#include "../Engine/Controls.hpp"

#include "Screens/SplashScreen.hpp"
#include "Screens/TitleScreen.hpp"
#include "Screens/CharacterSelectScreen.hpp"

class MainMenu : public Scene {
private:
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


    // In the future, consider making a stack of screens
    Screen* currentScreen;

    AnimatedObject ship = AnimatedObject ("resources/sprites/ship.png", 7, 7); 
    

    Phase currentPhase;
    //sf::SoundBuffer soundBuffer;
    //sf::Music theme;
    sf::Clock timer;

    int currentAlpha = 0;
    int fadePhase = 0;
    
    bool movingIn = true;

    bool updateScreen = false;

public:
    ~MainMenu () {
        if (currentScreen != nullptr)
            replaceScreen (nullptr);
    }
    MainMenu (GameSettings* gameSettings) : Scene (gameSettings)
    {
        

        backgroundTexture.loadFromFile ("resources/sprites/Night.png");
        background[0].setTexture (backgroundTexture);
        background[1].setTexture (backgroundTexture);
        background[0].setScale (10, 10);
        background[1].setScale (10, 10);

        currentPhase = SPLASH;

        currentScreen = new SplashScreen ();
        /*
        playButton.setImage ("resources/sprites/Play_Button.png", 4);
        playButton.addTag ("TITLE");
        playButton.setColor (sf::Color::Yellow);
        addElement (&playButton);

        settingsButton.setImage ("resources/sprites/Settings_Button.png", 4);
        settingsButton.addTag ("TITLE");
        addElement (&settingsButton);

        quitButton.setImage ("resources/sprites/Quit_Button.png", 4);
        quitButton.addTag ("TITLE");
        addElement (&quitButton);

        selectedButton = (Button*) getElements()[0];

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

        ///*theme.openFromFile ("resources/audio/Theme.wav");
        //theme.setLoopPoints (sf::Music::TimeSpan (sf::milliseconds (17600), sf::milliseconds (33270)));
        //theme.setLoop (true);
        //theme.play();
        timer.restart ();

        ship.getSprite().setScale (4, 4);
        ship.getSprite().setPosition (360, 360);
        ship.getSprite().setOrigin (15, 6);*/
    }
    void replaceScreen (Screen* newScreen) {
        
        Screen* oldScreen = currentScreen;
        currentScreen = newScreen;
        delete oldScreen;
        oldScreen = nullptr;
    }
    void eventHandler (sf::Event& e) {
        getRegistry()->eventHandler (e);
    }
    void update (float dt) {
        if (currentScreen == nullptr)
            return;
        
        getRegistry ()->update (dt);

        currentScreen->update (dt);
        updateScreen = currentScreen->screenIsFinished ();

        if (currentPhase != SPLASH) {
            for (int i = 0; i < 2; ++i) {
                if (background[i].getPosition ().x < -1000) {
                    background[i].setPosition (0, 0);
                }
                background[i].move (-dt * 500, 0);
            }
        }
        if (updateScreen) {
            std::string identifier = currentScreen->getExitIdentifier ();

            if (currentPhase == SPLASH) {
                currentPhase = TITLE;
                getRegistry()->clear();
                
                replaceScreen (new TitleScreen (getRegistry(), getController()));
            }
            else {
                if (currentPhase == TITLE) {
                    if (identifier == "Play") {
                        currentPhase = SELECT;
                        getRegistry()->clear();
                        replaceScreen (new CharacterSelectScreen (getRegistry(), getController ()));
                    }
                    else if (identifier == "Settings") {
                        // SettingsScreen
                        currentPhase = SETTINGS;
                    }
                    else if (identifier == "Exit") {
                        setExitInfo ("Exit");
                        exitScene = true;
                        // Quit
                    }
                }
                if (currentPhase == SELECT) {
                    if (identifier == "Back") {
                        currentPhase = TITLE;
                        getRegistry()->clear();
                        replaceScreen (new TitleScreen (getRegistry(), getController()));
                    }
                    else if (identifier == "Start") {
                        // We are replacing the entire scene
                        exitScene = true;
                        std::string selection = currentScreen->getAdditionalInfo ();
                        getRegistry()->clear();
                        if (selection == "Bacon Buddy") {
                            
                        }
                    }
                }
            }
            updateScreen = false;
        }
        /*
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
            // INPUT
            // 
            ship.update (dt, [this](float dt){
                ship.setPosition (360, 360 + (15 * std::sin (ship.elapsedTime * 3.6 / 3.14)));
            });
            for (int i = 0; i < 2; ++i) {
                if (background[i].getPosition ().x < -1000) {
                    background[i].setPosition (0, 0);
                }
                background[i].move (-dt * 500, 0);
            }
            
            if (movingIn) {
                if (titleSprite.getPosition().y < 180) {
                    titleSprite.move (0, dt * 100);
                }
                else {
                    titleSprite.setPosition (360, 180);
                    movingIn = false;
                }
            }
        }*/
    }


    void draw (sf::RenderWindow& window) {
        if (currentPhase != SPLASH) {
            window.draw (background[0]);
            window.draw (background[1]);
        }

        if (currentScreen != nullptr)
            currentScreen->draw (window);
        
        getRegistry()->draw(window);

        
        /*std::vector<UIElement*> e = getElements();

        switch (currentPhase) {
            case SPLASH:
                window.draw (splashSprite);
                break;
            case TITLE:
                window.draw (background[0]);
                window.draw (background[1]);
                ship.draw (window);
                window.draw (titleSprite);

                for (size_t i = 0; i < e.size(); ++i) {
                    UIElement* element = e[i];
                    if (element->hasTag ("TITLE"))
                        element->draw(window);
                }
                break;
            case SELECT:
                break;
            case SETTINGS:
                break;
            case SCORES:
                break;
        }*/
    }
};