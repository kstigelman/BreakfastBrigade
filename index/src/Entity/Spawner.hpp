#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Enemy.hpp"



using json = nlohmann::json;


class Spawner {
    private:
        Level* level;
        unsigned difficulty = 0;
    public:
        Spawner (Level* level) : level(level);
        ~Spawner () {

        }
        virtual Enemy* spawn(sf::Vector2f position) = 0;
        void setDifficulty (unsigned newDifficulty) {
            difficulty = newDifficulty;
        }
};

template <class T>
class SpawnerFor : public Spawner {
    public:
        virtual T* spawn(Level* level, sf::Vector2f position) { 
            entity_ = new T(level);
            entity_->setPosition (position);
            level->registerObject (entity_);
        }
};