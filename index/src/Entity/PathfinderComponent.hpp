#pragma once
#include "../Map/TileMap.hpp"
#include "../Engine/GameObject.hpp"
#include "../Engine/Transform.hpp"

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

        Transform* self;
        Transform* target;

        StateWrapper prevState = {IDLE, 0.0, 0.0, false}; 
        StateWrapper currentState = {IDLE, 0.0, 0.0, false};

        bool bNewState = false;

        float attackRange = 20.0f;
        sf::Vector2f direction;

        sf::Vector2f prevPosition;
    public:
        PathfinderComponent (Level* level, Transform* self, Transform* target = nullptr) 
        : tileMap (level->getMap ()->getTileMap ()), self(self), target(target) {
            
        }
        virtual sf::Vector2f getNextPosition () {
            return sf::Vector2f (0.0, 0.0);
        } 
        void setTarget (Transform* newTarget) {
            target = newTarget;
        };



        
        virtual void update (float dt) {
            prevPosition = self->position;
            
            if (self != nullptr && target != nullptr) {
                self->velocity = dt * (target->position - self->position);
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