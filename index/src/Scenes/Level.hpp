#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "../Map/Map.hpp"
class Level : public Scene {
    protected:
        Map map;
    public:
        Level (class GameSettings* gameSettings) : Scene (gameSettings) {

        }
        Map* getMap () {
            return &map;
        }

};