#pragma once
#include <SFML/Graphics.hpp>

class Screen {
private:
    std::string name;
    bool bFinished = false;
    std::set<sf::Keyboard::Key>* controller;

    std::string exitIdentifier = "null";
public:
    Screen (std::string name, std::set<sf::Keyboard::Key>* controller = nullptr) : name(name), controller(controller) {
    }

    virtual void update (float dt) = 0;
    virtual void draw (sf::RenderWindow& window) = 0;

    void setScreenFinished (bool newValue) {
        bFinished = newValue;
    }
    bool screenIsFinished () {
        return bFinished;
    }
    void setExitIdentifier (std::string identifier) {
        exitIdentifier = identifier;
    }
    std::string getExitIdentifier () {
        return exitIdentifier;
    }
    virtual std::string getAdditionalInfo () {
        return "null";
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