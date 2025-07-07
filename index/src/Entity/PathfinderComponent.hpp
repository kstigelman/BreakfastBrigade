#pragma once
#include "../Map/TileMap.hpp"
#include "../Engine/GameObject.hpp"
#include "../Engine/Transform.hpp"

class PathfinderComponent {
    private:
        TileMap* tileMap;
        Transform* target;
    public:
        PathfinderComponent (Level* level, Transform* target = nullptr) 
        : tileMap (level->getMap ()->getTileMap ()), target(target) {
            
        }
        virtual sf::Vector2f getNextPosition () {
            
        } 
        void setTarget (Transform* newTarget) {
            target = newTarget;
        };
};