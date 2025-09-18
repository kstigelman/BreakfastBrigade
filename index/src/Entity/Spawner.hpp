#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
//#include <nlohmann/json.hpp>

#include "../Engine/GameObject.hpp"



//using json = nlohmann::json;

class Spawner {
    private:
        
        unsigned difficulty = 0;
    public:
        Spawner () {}
        ~Spawner () {

        }
        virtual GameObject* spawn(Level* level, sf::Vector2f position) = 0;
        void setDifficulty (unsigned newDifficulty) {
            difficulty = newDifficulty;
        }
};

template <class T>
class SpawnerFor : public Spawner {
    public:

        virtual T* spawn(Level* level, sf::Vector2f position) { 
            T* object = new T(level);
            object->setPosition (position);
            level->registerObject (object);
            return object;
        }
};