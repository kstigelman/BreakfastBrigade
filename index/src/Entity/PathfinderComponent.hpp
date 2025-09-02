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
            
        } 
        void setTarget (Transform* newTarget) {
            target = newTarget;
        };

        /*
        // A* Search Algorithm
        1.  Initialize the open list
        2.  Initialize the closed list
            put the starting node on the open 
            list (you can leave its f at zero)
        3.  while the open list is not empty
            a) find the node with the least f on 
            the open list, call it "q"
            b) pop q off the open list
        
            c) generate q's 8 successors and set their 
            parents to q
        
            d) for each successor
                i) if successor is the goal, stop search
                
                ii) else, compute both g and h for successor
                successor.g = q.g + distance between 
                                    successor and q
                successor.h = distance from goal to 
                successor (This can be done using many 
                ways, we will discuss three heuristics- 
                Manhattan, Diagonal and Euclidean 
                Heuristics)
                
                successor.f = successor.g + successor.h
                iii) if a node with the same position as 
                    successor is in the OPEN list which has a 
                lower f than successor, skip this successor
                iV) if a node with the same position as 
                    successor  is in the CLOSED list which has
                    a lower f than successor, skip this successor
                    otherwise, add  the node to the open list
            end (for loop)
        
            e) push q on the closed list
            end (while loop)
        */
        sf::Vector2i aStar () {
            std::vector<sf::Vector2i> openList;
            std::vector<sf::Vector2i> closedList;

            openList.push_back (tileMap->convertToTileCoords (self->position.x, self->position.y));
            
            

        }
        std::vector<sf::Vector2i> expand (sf::Vector2i node) {
            std::vector<sf::Vector2i> openList;
            openList[0] = node + sf::Vector2i (1, 0);
            openList[1] = node + sf::Vector2i (-1, 0);
            openList[2] = node + sf::Vector2i (0, 1);
            openList[3] = node + sf::Vector2i (0, -1);
            return openList;
        }
        virtual void update (float dt) {
            prevPosition = self->position;
            
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