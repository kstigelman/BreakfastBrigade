#pragma once
#include <SFML/Graphics.hpp>

class Screen {
private:
    std::string name;
    bool bFinished = false;
    std::set<sf::Keyboard::Key>* controller;

    std::string exitIdentifier = "null";
public:
    Screen (std::string name, std::set<sf::Keyboard::Key>* controller = nullptr) : name(name), controller(controller) {}

    virtual void update (float dt);
    virtual void draw (sf::RenderWindow& window);

    void setScreenFinished (bool newValue) {
        bFinished = newValue;
    }
    bool screenIsFinished () {
        return screenIsFinished;
    }
    void setExitIdentifier (std::string identifier) {
        exitIdentifier = identifier;
    }
    std::string getExitIdentifier () {
        return exitIdentifier;
    }
    std::string getName () {
        return name;
    }

    void setController (std::set<sf::Keyboard::Key>* newController) {
        controller = newController;
    }
    std::set<sf::Keyboard::Key>* getController () {
        return controller;
    }
};