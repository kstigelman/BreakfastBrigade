#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

#include "Tile.hpp"


class Room {
    private:
        int id;
        sf::Vector2i size;
        std::vector<Tile> tileVector;
        //std::vector<Door> doors;

        int*
        parseLine (std::string line) {
            int length = line.length ();
            int* stream = new int[length + 1];

            for (int i = 0; i < length; ++i) {
                stream[i] = ((int) line[i]) - 48;
                printf ("%d", stream[i]);
            }
            printf ("\n");
            stream[length] = -1;
            return stream;
        }
        
        Tile
        getTileAt (int type, sf::Vector2i loc) {
            if (type == 1)
                return Floor (loc);
            if (type == 2)
                return Wall (loc);
            return Tile (loc);
        }
        
    public:
        Room (int roomId = 0, sf::Vector2i dimensions = sf::Vector2i (0, 0)) {
            size = dimensions;
            id = roomId;

            std::string filepath = "resources/maps/map_" + std::to_string (id);
            filepath += ".txt";

            std::ifstream input (filepath);

            if (!input)
                std::cout << "Failed to open map.\n";

            int column = 0;
            for (std::string line; getline (input, line);) {
                int* row = parseLine (line);
                int length = sizeof (*row);


                int* iter = row;
                int i = 0;
                while (*iter != -1) {
                    tileVector.push_back (getTileAt (row[i], sf::Vector2i (i, column)));
                    ++i;
                    ++iter;
                }
                /*for (int i = 0; i < length; ++i) {
                    
                    std::cout << row[i] << " ";
                }*/
                printf ("\n");
                ++column;
                size.x = length;
            }
            size.y = column;
        }
        sf::Vector2i
        getSize () {
            return size;
        }

        Tile
        getTile (sf::Vector2i location) {
            return tileVector[location.x + (location.y * size.x)];
        }

        Tile
        getTile (int index) {
            return tileVector[index];
        }
        int
        getWidth () {
            return size.x;
        }
        int
        getHeight () {
            return size.y;
        }
        /*
        Door*
        getDoor (int index) {
            if (index > doors.size() - 1)
                return nullptr;
            return &doors[index];
        }*/
        void
        draw (sf::RenderWindow& window) {
            for (size_t i = 0; i < tileVector.size (); ++i)
                tileVector[i].draw (window);
        }

};