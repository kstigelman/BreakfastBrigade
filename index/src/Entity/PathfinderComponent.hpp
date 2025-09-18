#pragma once
#include "../Map/TileMap.hpp"
#include "../Engine/GameObject.hpp"
#include "../Engine/Collider.hpp"
#include "../Engine/Transform.hpp"
#include "AI/A_Star.hpp"

enum AIState {
    IDLE,
    WANDER,
    FOLLOW,
    ATTACK
};

struct StateWrapper {
    AIState state;
    float length = 0.0;
    float ticksLeft = 0.0;
    bool endStateOverride = false;
};
class PathfinderComponent {
    private:
        TileMap* tileMap;

        Collider* self;
        Collider* target;
        A_Star a_star;

        StateWrapper prevState = {IDLE, 0.0, 0.0, false}; 
        StateWrapper currentState = {IDLE, 0.0, 0.0, false};

        bool bNewState = false;
        bool bFollowAStar = false;


        float attackRange = 20.0f;
        sf::Vector2f direction;

        sf::Vector2f prevPosition;

        std::vector<sf::Vector2i> path;
    public:
        PathfinderComponent (Level* level, Collider* self, Collider* target = nullptr) 
        : tileMap (level->getMap ()->getTileMap ()), self(self), target(target), a_star (level->getMap ()->getTileMap ()) {
            
        }
        virtual sf::Vector2f getNextPosition () {
            if (bFollowAStar && !path.empty ())
                return tileMap->convertToWorldCoords (path[0]) + sf::Vector2f (tileMap->getTileWidth() / 2, tileMap->getTileWidth() / 2);
            
            return self->getPosition ();//getFollowPosition ();
        }

        void setTarget (Collider* newTarget) {
            target = newTarget;
        };

        sf::Vector2f getFollowPosition () {
            return target == nullptr ? self->getPosition () : target->getPosition ();
        }

        
        virtual void update (float dt) {
            prevPosition = self->getPosition ();
            
            // Check if next position is blocked. If not, continue with follow
            // Otherwise, use A* search

            
            path = a_star.getPath (tileMap->convertToTileCoords (self->getPosition ()), 
                                       tileMap->convertToTileCoords (target->getPosition ()));

            bFollowAStar = true;
            /*
            if (tileMap->isTargetBlocked (*self) && target != nullptr) {
                path = a_star.getPath (tileMap->convertToTileCoords (self->getPosition ()), 
                                       tileMap->convertToTileCoords (target->getPosition ()));
                bFollowAStar = true;
            }
            else {
                bFollowAStar = false;
                //sf::Vector2f targetPos = target->getPosition ();

                //float dx = targetPos.x - self->getPosition().x;
                //float dy = targetPos.y - self->getPosition().y;
                  
                
                //path.push_back (sf::Vector2f (dx, dy));
                
                //velocity = sf::Vector2f( std::cos(a) * getMovementSpeed(), std::sin(a) * getMovementSpeed());
            }*/

            
            
            if (self != nullptr && target != nullptr) {
                //self->velocity = dt * (target->getPosition () - self->getPosition ());
            }
            if (currentState.endStateOverride || currentState.ticksLeft <= 0) {
                prevState = currentState;

            }
            switch (currentState.state) {
                case IDLE:
                    break;
                case WANDER:
                    break;
                case FOLLOW:
                    break;
                case ATTACK:
                    break;
                default:
                    break;
            }
        }
};