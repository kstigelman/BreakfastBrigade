#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


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
        A_Star () {

        }
        sf::Vector2i nextDirection (sf::Vector2i start, sf::Vector2i goal) {
            std::vector<Node> openList; // 1.  Initialize the open list
            std::vector<Node> closedList; // 2.  Initialize the closed list
            
            // put the starting node on the open list (you can leave its f at zero)
            openList.push_back ({nullptr, start});
            
            Node found;
            bool done = false;
            // 3.  while the open list is not empty
            while (!openList.empty () || !done) {
                // a) find the node with the least f on the open list, call it "q"
                int q_index = findLeastF (&openList);

                // b) pop q off the open list
                Node q = pop (&openList, q_index);

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
                    // ii) else, compute both g and h for successor 
                    //         successor.g = q.g + distance between successor and q
                    s.g = q.g + distance (s.position, q.position);
                    // successor.h = distance from goal to successor
                    s.h = manhattanDistance (s.position, q.position);
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
                closedList.push_back (q);
            }
            return found.position;
        }
        
    private:
        struct Node {
            Node* parent;
            sf::Vector2i position;
            int f = 0;
            int g = 0;
            int h = 0;
        };

        int findLeastF (std::vector<Node>* list) {
            if (list->empty ())
                return -1;

            int smallest = 0;
            
            for (size_t i = 1; i < list->size (); ++i) {
                if (list->at (i).f > list->at (smallest).f)
                    smallest = i;
            }
            return smallest;
        }

        std::vector<Node> open () {

        }
        Node pop (std::vector<Node>* list, int index) {
            Node node = list->at (index);
            std::swap (list[index], list[list->size() - 1]);
            list->pop_back ();
            return node;
        }
        std::vector<Node> generateSuccessors (Node& q) {
            std::vector<Node> list;

            
            list.push_back ({&q, q.position + sf::Vector2i (1, 0)});
            list.push_back ({&q, q.position + sf::Vector2i (-1, 0)});
            list.push_back ({&q, q.position + sf::Vector2i (0, 1)});
            list.push_back ({&q, q.position + sf::Vector2i (0, -1)});

            return list;
        }
        int distance (sf::Vector2i position1, sf::Vector2i position2) {
            int x_dist = position1.x - position2.x;
            int y_dist = position1.y - position2.y;
            return (x_dist * x_dist) + (y_dist * y_dist);
        }
        int manhattanDistance (sf::Vector2i position1, sf::Vector2i position2) {
            return std::abs (position1.x - position2.x) + std::abs (position1.y - position2.y);
        }

        bool existsWithLowerF (std::vector<Node>* list, Node& node) {
            for (size_t i = 0; i < list->size (); ++i) {
                Node current = list->at (i);

                if (current.position != node.position)
                    continue;
                
                if (current.f < node.f)
                    return true;
            }
            return false;
        }

};


