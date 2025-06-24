#pragma once
#include <SFML/Graphics.hpp>
#include <set>

#include "../UI/UIElement.hpp"
#include "../UI/UIRegistry.hpp"
#include "../Engine/GameSettings.hpp"

class Scene {
private:
    //std::vector<UIElement*> uiElements;
    UIRegistry uiRegistry;
    std::string sceneName = "NULL";
    std::string exitInfo = "NULL";

    std::set<sf::Keyboard::Key>* controller;
    GameSettings* gameSettings;
    bool bTick = false;
protected:
    bool exitScene = false;
public:
    Scene (GameSettings* gameSettings) : gameSettings(gameSettings), uiRegistry (gameSettings) {
        
    }

    ~Scene () {
        
        /*for (size_t i = 0; i < uiElements.size(); ++i) {
            delete uiElements[i];
        }
        uiElements.clear();*/
    }
    std::string getExitInfo () {
        return exitInfo;
    }
    void setExitInfo (std::string info) {
        exitInfo = info;
    }
    bool readyForExit () {
        return exitScene;
    }
    void setController (std::set<sf::Keyboard::Key>* newController) {
        controller = newController;
    }

    virtual void update (float dt) {
        // We should update a collision handler first
        // Then update all world objects
        // Manage entity list as necessary



        /*for (size_t i = 0; i < uiElements.size(); ++i) {
            uiElements[i]->update (dt);
        }*/
    }
    virtual void draw (sf::RenderWindow& window) {
        /*for (size_t i = 0; i < uiElements.size(); ++i) {
            uiElements[i]->draw (window);
        }*/
    }

    std::string getName () {
        return sceneName;
    }

    void setName (std::string newName) {
        sceneName = newName;
    }

    virtual void eventHandler (sf::Event& e) = 0;

    UIRegistry* getRegistry () {
        return &uiRegistry;
    }
    void addElement (UIElement* e) {
        uiRegistry.add (e);
    }
    std::set<sf::Keyboard::Key>* getController () {
        return controller;
    }
};