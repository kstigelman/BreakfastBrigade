#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "TileMap.hpp"

class Map
{
	protected:
		sf::RectangleShape background;
		sf::VertexArray walls;
		TileMap tilemap;
	public:
		Map(sf::Vector2f size = sf::Vector2f (64, 64)) : tilemap (size.x, size.y)
		{
			printf ("Map: Constructor");
			background.setSize(sf::Vector2f(size.x, size.x));
			background.setPosition(0, size.y - size.x);
			background.setFillColor(sf::Color(210, 190, 165));
			
			//walls.setPrimitiveType (sf::Quads);
			//walls.resize (16);
		}
		void update()
		{
			
		}
		void draw(sf::RenderWindow& window)
		{
			window.draw (tilemap);
		}
		TileMap* getTileMap () {
			return &tilemap;
		}
		bool isBlockedAt (float x, float y) {
			return tilemap.getAtCoordinate ((int) x % 32, (int) y % 32)->collidable;
		}
		void loadWalls () {
			sf::Vertex* quad = &walls[0];

			quad[0].position = sf::Vector2f (0, 0);
			quad[1].position = sf::Vector2f (32, 0);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);

			quad = &walls[1];

			quad[0].position = sf::Vector2f (32, 0);
			quad[1].position = sf::Vector2f (32, 32);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);

			quad = &walls[2];

			quad[0].position = sf::Vector2f (0, 0);
			quad[1].position = sf::Vector2f (32, 0);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);

			quad = &walls[3];

			quad[0].position = sf::Vector2f (0, 0);
			quad[1].position = sf::Vector2f (32, 0);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);

			quad = &walls[4];

			quad[0].position = sf::Vector2f (0, 0);
			quad[1].position = sf::Vector2f (32, 0);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);

			quad = &walls[5];

			quad[0].position = sf::Vector2f (0, 0);
			quad[1].position = sf::Vector2f (32, 0);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);

			quad = &walls[6];

			quad[0].position = sf::Vector2f (0, 0);
			quad[1].position = sf::Vector2f (32, 0);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);

			quad = &walls[7];

			quad[0].position = sf::Vector2f (0, 0);
			quad[1].position = sf::Vector2f (32, 0);
			quad[2].position = sf::Vector2f (0, 32);
			quad[3].position = sf::Vector2f (32, 32);
		}
};
