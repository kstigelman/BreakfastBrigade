#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "../UI/AnimatedObject.hpp"
#include "../UI/Button.hpp"
#include "../UI/TextBox.hpp"
#include "../Engine/Controls.hpp"

class GameOverScreen : public Screen {
private:
    Button quitButton;
    Button retryButton;
    
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
    std::vector<TextBox*> textboxes;

    sf::Vector2f offset;
public:
    ~GameOverScreen () {
        uiRegistry->clear ();

        quitButton.setVisibility (false);

        for (TextBox* tb : textboxes) {
            if (tb == nullptr)
                continue;
            delete tb;
            tb = nullptr;
        }
    }
    GameOverScreen (UIRegistry* registry, std::set<sf::Keyboard::Key>* controller) : Screen ("GameOver", controller),
        retryButton(registry, "Retry", sf::Vector2f (192, 500), sf::Vector2f (100, 50)),
        quitButton(registry, "Quit", sf::Vector2f (308, 500), sf::Vector2f (100, 50))
    {
        uiRegistry = registry;
     
        textboxes.push_back (new TextBox ("GAME OVER!", sf::Vector2f (0, 0), -1, 60, sf::Color::Red, true));
        textboxes.push_back (new TextBox ("Press Q to go back to the main menu", sf::Vector2f (0, 70), -1, 30, sf::Color::Red, true));
        quitButton.setImage ("resources/sprites/Quit_Button.png", 4);
        quitButton.addTag ("QUIT");
        quitButton.setOnClicked ([this](){
            this->setScreenFinished (true);
            this->setExitIdentifier ("QuitToTitle");
        });
        retryButton.addTag ("RETRY");
        retryButton.setOnClicked ([this] () {
            this->setScreenFinished(true);
            this->setExitIdentifier ("Restart");
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
        if (isFixed ()) {

        }
        else {

        }
				
    }
    void update (float dt) override {
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Q)) {
            setExitIdentifier ("Quit");
            setScreenFinished (true);
        }
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

        /*for (int i = 0; i < 2; ++i) {
            if (background[i].getPosition ().x < -1000) {
                background[i].setPosition (0, 0);
            }
            background[i].move (-dt * 500, 0);
        }*/
        
    }
    void draw (sf::RenderWindow& window) override {
        //window.draw (background[0]); MOVED TO MAIN MENU
        //window.draw (background[1]);
        for (TextBox* tb : textboxes) {
            if (tb != nullptr)
                tb->draw (window);
        }
        // We shouldn't have to draw uiRegistry
    }


};