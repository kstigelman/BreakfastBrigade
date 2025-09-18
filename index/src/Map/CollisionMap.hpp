#pragma once
#include <SFML/Graphics.hpp>
#include "../Engine/Collider.hpp"
#include "TileMap.hpp"

class CollisionMap : public Collider {
    private:
        std::vector<int> collisionMap;
        sf::Vector2i mapSize;
    public:
        CollisionMap (std::vector<TileMap*> tileMaps) {
            
            int size = 0;
            for (size_t i = 0; i < tileMaps.size(); ++i) {
                size += tileMaps[i]->getSize().x * tileMaps[i]->getSize().y;
                mapSize = tileMaps[i]->getSize();
            }

            collisionMap.resize((size / 32) + 1);
        }
        
        void updateMap (bool newValue, int x, int y) {
            int pos = x + (y * mapSize.x);
            int bitPos = 7 - (pos % 8);

            // Some sneaky bit-wise logic to update the map location
            collisionMap[pos / 8] = collisionMap[pos / 8] | (newValue << bitPos);
        }
        // [1 1 1 0 0 0 0 1]
        // FIXED: We need to somehow reverse this int in order to truly map this. because ints are read r -> l
        bool isTileBlocking (int x, int y) {
            int pos = x + (y * mapSize.x);
            int bitPos = 7 - (pos % 8);

            // Some even sneakier bit-wise logic to check if the map is blocking
            return 1 & (collisionMap[pos / 8] >> bitPos);
        }
};