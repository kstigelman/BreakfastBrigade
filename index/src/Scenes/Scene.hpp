#pragma once
#include <SFML/Graphics.hpp>
#include <set>

#include "../UI/UIElement.hpp"
#include "../UI/UIRegistry.hpp"
#include "../Engine/GameSettings.hpp"
#include "../Engine/GameObject.hpp"


class Scene {
private:
    //std::vector<UIElement*> uiElements;
    std::vector<GameObject*> objectCollection;
    std::vector<UIElement*> uiCollection;

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
        printf ("Scene: Constructor");
    }
    ~Scene () {
        for (GameObject* o : objectCollection) {
            if (o == nullptr) continue;

            delete o;
            o = nullptr;
        }
        objectCollection.clear ();
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
    virtual void eventHandler (sf::Event& e) = 0;

    void spawn(GameObject* entity_, sf::Vector2f position) { 
        objectCollection.push_back (entity_);
        entity_->setPosition (position);
        entity_->setShouldDraw (true);
        entity_->setActive (true);
    }

    void create (UIElement* element_) {
        uiCollection.push_back (element_);
        uiRegistry.add (element_);
    }

    UIRegistry* getRegistry () {
        return &uiRegistry;
    }
    std::vector<GameObject*>& getGameObjects () {
        return objectCollection;
    }

    virtual void registerObject (GameObject* object) {
        objectCollection.push_back (object);
    }
    virtual void registerProjectile (class Projectile* p) {
        
    };
    
    std::string getExitInfo () {
        return exitInfo;
    }
    void setExitInfo (std::string info) {
        exitInfo = info;
    }
    bool readyForExit () {
        return exitScene;
    }
    virtual void setController (std::set<sf::Keyboard::Key>* newController) {
        controller = newController;
    }
    std::set<sf::Keyboard::Key>* getController () {
        return controller;
    }



    std::string getName () {
        return sceneName;
    }

    void setName (std::string newName) {
        sceneName = newName;
    }


    void addElement (UIElement* e) {
        uiRegistry.add (e);
    }

};