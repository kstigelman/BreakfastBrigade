#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Entity.hpp"



using json = nlohmann::json;


class Spawner {
    private:
        Entity* prototype_;
    public:
        Spawner (std::string jsonFile) {
            std::ifstream file(jsonFile);
            json data = json::parse(file);
            
        }
        Entity* spawn () {
            return prototype_;
        }
        

};