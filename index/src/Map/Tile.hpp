#pragma once

#include <SFML/Graphics.hpp>


// 0 - Air
// 1 - Rock

struct Tile {
    // This is it's tile map location
    sf::Vector2f tilePosition = sf::Vector2f (0.0, 0.0);
    // This is it's world location (tilePosition * tile_width)
    sf::Vector2i position = sf::Vector2i (0, 0);
    int tileType = 0; // AIR
	bool collidable = false;
};

// Old Tile class -- for reference
/*
class Tile {
    protected:
        bool rigid;
        int type;
        bool sloped;
        sf::Vector2i location;
        sf::Vector2i tileSize;
        sf::RectangleShape tile;
    public:
        Tile(sf::Vector2i vLocation = sf::Vector2i(0, 0)) {
            tileSize = sf::Vector2i (32, 32);

            rigid = false;
            type = 0;
            sloped = false;
            tile.setSize (sf::Vector2f (tileSize.x, tileSize.y));
            setPosition (vLocation);
        }

        void
        setPosition (sf::Vector2i newLocation) {
            location = newLocation;
            tile.setPosition (sf::Vector2f (newLocation.x * tileSize.x, newLocation.y * tileSize.y));
        }
        int
        getType () {
            return type;
        }

        int
        isRigid () {
            return rigid;
        }

        int
        isSloped () {
            return sloped;
        }

        sf::Vector2i 
        getLocation () {
            return location;
        }

        int 
        getX () {
            return location.x;
        }
        int getY () {
            return location.y;
        }

        void
        draw (sf::RenderWindow& window) {
            window.draw (tile);
        }
};
class Wall : public Tile {
    public:
        Wall (sf::Vector2i vLocation = sf::Vector2i(0, 0))
         : Tile (vLocation) {
            rigid = true;
            type = 1;
            tile.setFillColor (sf::Color::White);
        }
};
class Floor : public Tile {
    public:
    Floor (sf::Vector2i vLocation = sf::Vector2i(0, 0))
     : Tile (vLocation) {
        rigid = false;
        type = 2;
        tile.setFillColor (sf::Color::Green);
    }*/