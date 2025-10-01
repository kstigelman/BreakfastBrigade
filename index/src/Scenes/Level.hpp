#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "../Map/Map.hpp"



class Level : public Scene {
    protected:
        Map map;
    public:
        Level (GameSettings* gameSettings) : Scene (gameSettings) {
            printf ("Level: Constructor");
        }
        Map* getMap () {
            return &map;
        }
        std::vector<GameObject*> getEntitiesByTag (std::string tag) {
            std::vector<GameObject*> entityList;
            
            for (GameObject* obj : getGameObjects ()) {

                if (obj && obj->getTags ().count (tag) > 0)
                    entityList.push_back (obj);
            }
            return entityList;
        }
        /*std::vector<Entity*> getEntitiesByName (std::string name) {
            std::vector<Entity*> entityList;
            
            for (GameObject* obj : getGameObjects ()) {

                Entity* e = dynamic_cast<Entity*> (obj);
                if (e && e->getName () == name)
                    entityList.push_back (e);
            }
            return entityList;
        }*/
};