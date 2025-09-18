#pragma once
#include <math.h>

#include "Entity.hpp"
#include "PathfinderComponent.hpp"

class Friend : public Entity {
    private:
        bool bFound = false;
        Entity* target;

        Collider searchCollider;
        PathfinderComponent pathfinder;
    public:
        Friend (Level* scene) : Entity (scene), searchCollider (sf::RectangleShape (sf::Vector2f (70, 70))), pathfinder (scene, &getCollider (), &getCollider ()) {
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
				//pathfinding (dt);
				Entity::update (dt);

                if (!bFound) {
                    if (target != nullptr) {
                        if (searchCollider.isColliding (target->getCollider ())) {
                            // Add this friend to the ship
                            setFound (true);
                            
                        }
                    }
                }
                else {
                    pathfinder.update (dt);
                    move (sf::Vector2f (velocity.x * dt, velocity.y * dt));

                    if (velocity != sf::Vector2f (0, 0))
                        animator.nextFrame ();
				
                }
            }
        }
        bool isFound () {
            return bFound;
        }
        virtual void setPosition(sf::Vector2f position) override {
			Entity::setPosition (position);
            searchCollider.setPosition (getPosition ());
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