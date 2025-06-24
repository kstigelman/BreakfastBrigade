#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Collider.hpp"
#include "../Map/CollisionMap.hpp"

class CollisionHandler {
	private:
        CollisionMap* map;
        std::vector<Collider*> entityColliders;
    public:
        CollisionHandler () {

        }
        void update (float dt) {
            for (size_t i = 0; i < entityColliders.size(); ++i) {
                for (size_t j = 0; j < entityColliders.size(); ++j) {
                    if (i == j)
                        continue;
                    if (entityColliders[i]->intersects (*entityColliders[j])) {
                        entityColliders[i]
                    }
                }
            }
        }
};