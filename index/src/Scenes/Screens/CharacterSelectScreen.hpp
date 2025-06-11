#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "../UI/AnimatedObject.hpp"
#include "../UI/Button.hpp"
#include "../Engine/Controls.hpp"

#include "../UI/SelectionBox.hpp"

class CharacterSelectScreen : public Screen
{
private:
    //std::vector<Button*> buttons;

    Button leftSelectButton;
    Button rightSelectButton;

    Button backButton;
    Button startButton;

    SelectionBox selectionBox;

    int selectedIndex = 0;

    UIRegistry* uiRegistry;
public:
    ~CharacterSelectScreen () {
        uiRegistry->clear ();
    }
    CharacterSelectScreen (UIRegistry* registry, std::set<sf::Keyboard::Key>* controller) : Screen ("Character Select", controller),
      leftSelectButton(registry, "Left Select", sf::Vector2f (100, 200), sf::Vector2f (50, 50)),
      rightSelectButton(registry, "Right Select", sf::Vector2f (400, 200), sf::Vector2f (50, 50)), 
      backButton (registry, "Back", sf::Vector2f (20, 20), sf::Vector2f (50, 20)),
      startButton (registry, "Start", sf::Vector2f (100, 400), sf::Vector2f (100, 50)),
      selectionBox (registry)
    {
        uiRegistry = registry;
        backButton.setImage ("resources/sprites/Back_Button.png");
        backButton.setOnClicked ([this] {
            this->setExitIdentifier ("Back");
            this->setScreenFinished (true);
        });
        startButton.setImage ("resources/sprites/Play_Button.png");
        startButton.setOnClicked ([this] {
            this->setExitIdentifier ("Start");
            this->setScreenFinished (true);
        });

        sf::Texture texture;
        texture.loadFromFile ("resources/sprites/Buddy_Frame.png");
        selectionBox.addSlot ("Bacon Buddy", texture);
        //leftSelectButton.setImage ("resources/sprites/Left_Arrow.png", 4);
        //leftSelectButton.addTag ("CharacterSelect");

        /*leftSelectButton.setOnClicked ([this](){
            setScreenFinished (true);
            setExitIdentifier ("Play");
        });

        buttons.push_back (&leftSelectButton);
        buttons.push_back (&rightSelectButton);
        buttons.push_back (&backButton);
        */
    }
    void update (float dt) {

    }
    void draw (sf::RenderWindow& window) {
        selectionBox.draw (window);
        //backButton.draw (window);
        //startButton.draw (window);
    }
    std::string getAdditionalInfo () override {
        return selectionBox.getSelection ();
    }

};