#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "../UI/AnimatedObject.hpp"
#include "../UI/Button.hpp"
#include "../Engine/Controls.hpp"

class PauseMenu : public Screen {
private:
   sf::Texture backgroundTexture;
    sf::Sprite background[2];

    sf::Texture title;
    sf::Sprite titleSprite;

    Button playButton;
    Button settingsButton;
    Button quitButton;

    
    //std::vector<Button*> buttons;
    int selectedIndex = 0;

    AnimatedObject ship = AnimatedObject ("resources/sprites/ship.png", 7, 7); 
    


    //sf::SoundBuffer soundBuffer;
    //sf::Music theme;
    sf::Clock timer;

    int currentAlpha = 0;
    int fadePhase = 0;
    
    bool movingIn = true;

    bool updateScreen = false;
    UIRegistry* uiRegistry;
public:
    ~PauseMenu () {
        uiRegistry->clear ();
        playButton.setVisibility (false);
        settingsButton.setVisibility (false);
        quitButton.setVisibility (false);
    }
    PauseMenu (UIRegistry* registry, std::set<sf::Keyboard::Key>* controller) : Screen ("Title", controller),
        playButton(registry, "Resume", sf::Vector2f (308, 440), sf::Vector2f (100, 50)),
        quitButton(registry, "Quit", sf::Vector2f (308, 500), sf::Vector2f (100, 50))
    {
        uiRegistry = registry;
        
        playButton.setImage ("resources/sprites/Play_Button.png", 4);
        playButton.addTag ("PAUSE");

        playButton.setOnClicked ([this](){
            this->setScreenFinished (true);
            this->setExitIdentifier ("Resume"); 
        });
        
        //buttons.push_back (&playButton);

        settingsButton.setImage ("resources/sprites/Settings_Button.png", 4);
        settingsButton.addTag ("TITLE");
        settingsButton.setOnClicked ([this](){
            this->setScreenFinished (true);
            this->setExitIdentifier ("Settings");
        });
        //buttons.push_back (&settingsButton);

        quitButton.setImage ("resources/sprites/Quit_Button.png", 4);
        quitButton.addTag ("PAUSE");
        quitButton.setOnClicked ([this](){
            this->setScreenFinished (true);
            this->setExitIdentifier ("Quit");
        });
        //buttons.push_back (&quitButton);
        
        //background[1].setPosition (1000, 0);
        //soundBuffer.loadFromFile ("resources/audio/Theme.wav");

        /*theme.openFromFile ("resources/audio/Theme.wav");
        theme.setLoopPoints (sf::Music::TimeSpan (sf::milliseconds (17600), sf::milliseconds (33270)));
        theme.setLoop (true);
        theme.play();*/
        timer.restart ();


    }
    void setPosition (sf::Vector2f position) override {

    }
    void update (float dt) override {
        //buttons[selectedIndex]->onHovered ();


        /*if (getController() != nullptr) {
            if (getController()->count (SELECT_BUTTON)) {
                buttons[selectedIndex]->onClicked ();
            }
            else if (getController()->count (MOVE_DOWN)) {
                if (selectedIndex < buttons.size() - 1)
                    ++selectedIndex;
                else
                    selectedIndex = buttons.size() - 1;
            }
            else if (getController()->count (MOVE_UP)) {
                if (selectedIndex > 0)
                    --selectedIndex;
                else
                    selectedIndex = 0;
            }

        } */ 
            /*

            if (playButton.isClicked ()) {
                
            }*/

            // 
        ship.update (dt, [this](float dt){
            ship.setPosition (360, 360 + (15 * std::sin (ship.elapsedTime * 3.6 / 3.14)));
        });
        /*for (int i = 0; i < 2; ++i) {
            if (background[i].getPosition ().x < -1000) {
                background[i].setPosition (0, 0);
            }
            background[i].move (-dt * 500, 0);
        }*/
        
        if (movingIn) {
            if (titleSprite.getPosition().y < 180) {
                titleSprite.move (0, dt * 100);
            }
            else {
                titleSprite.setPosition (360, 180);
                movingIn = false;
            }
        }
    }
    void draw (sf::RenderWindow& window) override {
        //window.draw (background[0]); MOVED TO MAIN MENU
        //window.draw (background[1]);
        ship.draw (window);
        window.draw (titleSprite);

    }


};