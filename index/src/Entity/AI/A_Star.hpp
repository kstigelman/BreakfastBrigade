#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../../Map/TileMap.hpp"

/* A* Search Algorithm
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
                successor.g = q.g + distance between successor and q
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


class A_Star {
    public:
        A_Star (TileMap* map) : mMap (map) {

        }
        std::vector<sf::Vector2i> getPath (sf::Vector2i start, sf::Vector2i goal) {
 
            /*
            if (!hasGoalChanged(goal)) {
                if (mPath.size () <= 1)
                    return mPath;
                if (start == mPath[0])
                    mPath.erase (mPath.begin ());
                return mPath;
            }*/
            if (mPath.size() > 0) {
                prevNodes[1] = prevNodes[0];
                prevNodes[0] = mPath[0];
            }
            mPath.clear ();    

            mStart = start;
            mGoal = goal;

            std::vector<Node> openList; // 1.  Initialize the open list
            std::vector<Node> closedList; // 2.  Initialize the closed list
            
            // put the starting node on the open list (you can leave its f at zero)
            openList.push_back ({nullptr, start, 0, 0, manhattanDistance (start, goal)});
            
            Node found;
            bool done = false;
            int count = 0;
            // 3.  while the open list is not empty
            while (!openList.empty () && !done && count < depthLimit) {
                ++count;
                // a) find the node with the least f on the open list, call it "q"
                int q_index = findLeastF (&openList);

                if (q_index < 0) {
                    found = openList[0];
                    done = true;
                    break;
                }
                // b) pop q off the open list
                //Node q = pop (&openList, q_index);
                Node q = openList.at (q_index);
                openList.erase (openList.begin () + q_index);
                   
                closedList.push_back (q);  
                if (q.position != start)
                    mPath.push_back (q.position);
                
                if (q.position == goal) {
                    done = true;
                    break;
                }

            
                // c) generate q's 8 successors and set their parents to q
                std::vector<Node> successors = generateSuccessors (q);

                // d) for each successor
                for (size_t i = 0; i < successors.size (); ++i) {
                    Node s = successors[i];

                    // i) if successor is the goal, stop search
                    if (s.position == goal) {
                        found = s;
                        done = true;
                        break;
                    }
                    //if (prevNodes[0] == s.position)
                    //    continue;
                    //if (prevNodes[1] == s.position)
                    //    continue;
                    // ii) else, compute both g and h for successor 
                    //         successor.g = q.g + distance between successor and q
                    s.g = distance (s.position, start);
                    // successor.h = distance from goal to successor
                    s.h = manhattanDistance (s.position, goal);
                    // successor.f = successor.g + successor.h
                    s.f = s.g + s.h;

                    // iii) if a node with the same position as successor is in the OPEN list 
                    //      which has a lower f than successor, skip this successor
                    if (existsWithLowerF (&openList, s))
                        continue;
                    // iV) if a node with the same position as successor  is in the CLOSED list 
                    //     which has a lower f than successor, skip this successor otherwise, add  the node to the open list
                    if (existsWithLowerF (&closedList, s))
                        continue;
                    
                    
                    openList.push_back (s);
                }
                // e) push q on the closed list

            }
            return mPath;
        }
        
    private:

        struct Node {
            Node* parent;
            sf::Vector2i position;
            float f = 0;
            float g = 0;
            float h = 0;
        };
        std::vector<sf::Vector2i> mPath;
        sf::Vector2i mStart;
        sf::Vector2i mGoal;
        TileMap* mMap;

        int depthLimit = 20;

        sf::Vector2i prevNodes[2] = { sf::Vector2i (0, 0) };

        int findLeastF (std::vector<Node>* list) {
            if (list->empty ())
                return -1;

            int smallest = 0;
            
            for (size_t i = 1; i < list->size (); ++i) {
                if (list->at (i).f < list->at (smallest).f)
                    smallest = i;
            }
            return smallest;
        }
        bool hasGoalChanged (sf::Vector2i newGoal) {
            return newGoal != mGoal;
        }
        Node pop (std::vector<Node>* list, int index) {
            Node node = list->at (index);
            std::swap (list[index], list[list->size() - 1]);
            list->pop_back ();
            return node;
        }
        std::vector<Node> generateSuccessors (Node& q) {
            std::vector<Node> list;

            Node right = {&q, q.position + sf::Vector2i (1, 0)};
            Node left = {&q, q.position + sf::Vector2i (-1, 0)};
            Node down = {&q, q.position + sf::Vector2i (0, 1)};
            Node up = {&q, q.position + sf::Vector2i (0, -1)};
            
            if (!mMap->getTileAt (right.position)->collidable)
                list.push_back (right);

            if (!mMap->getTileAt (left.position)->collidable)
                list.push_back (left);

            if (!mMap->getTileAt (up.position)->collidable)
                list.push_back (up);

            if (!mMap->getTileAt (down.position)->collidable)
                list.push_back (down);

            return list;
        }
        float distance (sf::Vector2i position1, sf::Vector2i position2) {
            int x_dist = position1.x - position2.x;
            int y_dist = position1.y - position2.y;
            return std::sqrt ((x_dist * x_dist) + (y_dist * y_dist));
        }
        float manhattanDistance (sf::Vector2i position1, sf::Vector2i position2) {
            return std::abs (position1.x - position2.x) + std::abs (position1.y - position2.y);
        }

        bool existsWithLowerF (std::vector<Node>* list, Node& node) {
            for (size_t i = 0; i < list->size (); ++i) {
                Node current = list->at (i);

                if (current.position != node.position)
                    continue;
                
                if (current.g < node.g)
                    return true;
            }
            return false;
        }

};


