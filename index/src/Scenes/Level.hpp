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
        std::vector<Entity*> getEntitiesByTag (std::string tag) {
            std::vector<Entity*> entityList;
            
            for (GameObject* obj : getGameObjects ()) {

                Entity* e = dynamic_cast<Entity*> (obj);
                if (e && e->getTags ().count (tag) > 0)
                    entityList.push_back (e);
            }
            return entityList;
        }
        std::vector<Entity*> getEntitiesByName (std::string name) {
            std::vector<Entity*> entityList;
            
            for (GameObject* obj : getGameObjects ()) {

                Entity* e = dynamic_cast<Entity*> (obj);
                if (e && e->getName () == name)
                    entityList.push_back (e);
            }
            return entityList;
        }
};