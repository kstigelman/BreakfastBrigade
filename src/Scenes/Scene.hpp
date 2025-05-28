#pragma once
#include <SFML/Graphics.hpp>
#include <set>

#include "UI/UIElement.hpp"

class Scene {
private:
    std::vector<UIElement*> uiElements;
    std::string sceneName = "NULL";

    std::set<sf::Keyboard::Key>* controller;
    class Game* gameRef;
public:
    Scene () {
        
    }
    Scene (Game* game) {
        gameRef = game;
    }
    ~Scene () {
        for (size_t i = 0; i < uiElements.size(); ++i) {
            delete uiElements[i];
        }
        uiElements.clear();
    }
    void setController (std::set<sf::Keyboard::Key>* newController) {
        controller = newController;
    }

    virtual void update (float dt) {
        for (size_t i = 0; i < uiElements.size(); ++i) {
            uiElements[i]->update (dt);
        }
    }
    virtual void draw (sf::RenderWindow& window) {
        for (size_t i = 0; i < uiElements.size(); ++i) {
            uiElements[i]->draw (window);
        }
    }

    std::string getName () {
        return sceneName;
    }

    void setName (std::string newName) {
        sceneName = newName;
    }

    void addElement (UIElement* e) {
        uiElements.push_back (e);
    }
    std::vector<UIElement*> getElements () {
        return uiElements;
    }
    std::set<sf::Keyboard::Key>* getController () {
        return controller;
    }
    Game* getGameReference () {
        return gameRef;
    }
};