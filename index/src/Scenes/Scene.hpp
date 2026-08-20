#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <vector>
#include <functional>

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

    std::string inputMode = "MOUSE";


protected:
    bool exitScene = false;
    Screen* currentScreen;
    std::vector<std::function<void()>> deferredFunctions;
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

        if (currentScreen) {
            removeScreen ();
        }
        // Last update-- working on removing screens from inherited classes and working on inserting here
    }

    virtual void update (float dt) {
        // We should update a collision handler first
        // Then update all world objects
        // Manage entity list as necessary

        if (currentScreen) {
            currentScreen->update (dt);
            if (currentScreen->screenIsFinished ()) {
                if (currentScreen->getExitIdentifier() == "QuitToTitle") {
                    setExitInfo ("QuitToTitle");
                    setReadyForExitScene (true);
                }
                if (currentScreen->getExitIdentifier () == "Restart") {
                    setExitInfo ("Play");
                    setReadyForExitScene(true);
                }
            }
            return;
        }

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
    Screen* getCurrentScreen () {
        return currentScreen;
    } 
    void replaceScreen (Screen* newScreen) {    
        Screen* oldScreen = currentScreen;
        currentScreen = newScreen;
        delete oldScreen;
        oldScreen = nullptr;
    }
    void removeScreen () {
        replaceScreen (nullptr);
    }

    std::vector<GameObject*>& getGameObjects () {
        return objectCollection;
    }

    virtual void registerObject (GameObject* object) {
        objectCollection.push_back (object);
    }
    virtual void registerObject (GameObject* object, sf::Vector2f position) {
        objectCollection.push_back (object);
        object->setPosition (position);
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
    void setReadyForExitScene (bool newExitValue) {
        exitScene = newExitValue;
    }
    virtual void setController (std::set<sf::Keyboard::Key>* newController) {
        controller = newController;
    }
    std::set<sf::Keyboard::Key>* getController () {
        return controller;
    }

    std::vector<GameObject*> getObjectsByTag (std::string tag) {
        std::vector<GameObject*> objsList;
        for (GameObject* obj : objectCollection) {
            if (obj->getTags().count (tag) > 0)
                objsList.push_back (obj);
        } 
        return objsList;
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

    void addInputFunction (std::function<void()> newFunc) {
        deferredFunctions.push_back (newFunc);
    }
    void runInputFunctions () {
        for (std::function<void()> f : deferredFunctions) {
            f();
        }
    }
    GameSettings* getGameSettings () {
        return gameSettings;
    }

};