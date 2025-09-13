#pragma once
#include <math.h>

#include "Entity.hpp"


class Friend : public Entity {
    private:
        bool bFound = false;
        Entity* target;
    public:
        Friend (Level* scene) : Entity (scene) {
            tag = "Friend";
        }
        ~Friend () {

        }
        /*void update (float dt) {
            if (target != nullptr) {
                // Get pathfinder valid next tile location
                // Get current tile location
                // Move towards the new location
            }
        }*/
        virtual void update (float dt)
		{
			if (isActive())
			{
				pathfinding (dt);
				Entity::update (dt);
				move (sf::Vector2f (velocity.x * dt, velocity.y * dt));
				if (velocity != sf::Vector2f (0, 0))
					animator.nextFrame ();
				
				if (target != nullptr) {
					if (collider.isColliding (target->getCollider ())) {
						// Add this friend to the ship
					}
				}
            }
        }
        bool isFound () {
            return bFound;
        }
        void setFound (bool newVal) {
            bFound = newVal;
        }
        Entity* getTarget () {
            return target;
        }
        void setTarget (Entity* newTarget) {
            target = newTarget;
        }
        void pathfinding (float dt)
		{
			if (target == nullptr) {
				velocity = sf::Vector2f (0, 0);
				return;
			}

			sf::Vector2f targetPos = target->getPosition ();

			float dx = targetPos.x - sprite.getPosition().x;
			float dy = targetPos.y - sprite.getPosition().y;
				
			float a = std::atan2(dy, dx);
			
			velocity = sf::Vector2f( std::cos(a) * getMovementSpeed(), std::sin(a) * getMovementSpeed());
        }
        
};