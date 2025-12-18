#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "../Map/Map.hpp"
#include "../Entity/Projectile.hpp"


class Level : public Scene {
    protected:
        Map map;

        std::vector<Projectile*> projectileCollection;
    public:
        Level (GameSettings* gameSettings) : Scene (gameSettings) {
            printf ("Level: Constructor");
        }
        ~Level () {
            clearProjectiles ();
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
        void registerProjectile (Projectile* p) override {
            projectileCollection.push_back (p);
        }

        void clearProjectiles () {
            for (Projectile* p : projectileCollection)
                if (p != nullptr)
                    delete p;
            projectileCollection.clear ();
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