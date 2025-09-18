#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Tile.hpp"
#include "Collider.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        TileMap (int width, int height) {
            printf ("TileMap: Constructor");
            size = width * height;
            mapSize = sf::Vector2i (width, height);
            tiles = new Tile[width * height];
                                           
            tileWidth = 24;
            
            std::ifstream input;
            char* readArray = new char[width * height];
            input.open ("resources/world/world1.txt");

            for (size_t j = 0; j < height; ++j) {
                for (size_t i = 0; i < width; ++i) {
                    Tile* tile = &tiles[i + (j * width)];
                    tile->position = sf::Vector2i (i, j);
                    tile->tilePosition = sf::Vector2f (i * tileWidth, j * tileWidth);
                    /*
                    if (i < borderWidth || i > width - borderWidth - 1 || j < borderWidth || j > height - borderWidth - 1) {
                        tile->collidable = true;
                        tile->tileType = 1;
                    }*/
            
                    input >> readArray[i + j * width];

                    if (readArray[i + j * width] == '1') {
                        tile->collidable = true;
                        tile->tileType = 1;
                    }
                    //tiles[i + (j * width)] = tile;
                }
            }
            input.close ();
            load ("resources/sprites/Tiles.png", "N/A", sf::Vector2i (24, 24), width, height, sf::Vector2f (0, 0));

        }
        ~TileMap () {
            delete[] tiles;
            tiles = nullptr;
        }
        sf::Vector2i getSize () {
            return mapSize;
        }

        int getScale () {
            return scale;
        }
        int getTileWidth () {
            return tileWidth;
        }
        Tile* getTileAtCoordinate (float x, float y) {
            sf::Vector2i castCoordinates = convertToTileCoords (x, y);
            return &tiles[castCoordinates.x + (castCoordinates.y * mapSize.x)];
        }
        Tile* getTileAtCoordinate (sf::Vector2f position) {
            return getTileAtCoordinate (position.x, position.y);
        }
        Tile* getTileAt (sf::Vector2i position) {
            return &tiles[position.x + (position.y * mapSize.x)];
        }
        Tile* getTileAt (int x, int y) {
            return &tiles[x + (y * mapSize.x)];
        }
        sf::Vector2i convertToTileCoords (float x, float y) {
            return sf::Vector2i ((int) ((x - initPos.x) / tileSizePx.x), (int) ((y - initPos.y) / tileSizePx.y));
        }
        sf::Vector2i convertToTileCoords (sf::Vector2f position) {
            return sf::Vector2i ((int) ((position.x - initPos.x) / tileSizePx.x), (int) ((position.y - initPos.y) / tileSizePx.y));
        }
        sf::Vector2f convertToWorldCoords (sf::Vector2i position) {
            return sf::Vector2f ((position.x * tileSizePx.x) + initPos.x,  (position.y * tileSizePx.y) + initPos.y);
        }
        sf::Vector2f convertToWorldCoords (int x, int y) {
            return sf::Vector2f ((x * tileSizePx.x) + initPos.x,  (y * tileSizePx.y) + initPos.y);
        }
        bool isCoordinateOutsideOfMap (float x, float y) {
            return (x < initPos.x || 
                    y < initPos.y || 
                    x > initPos.x + (mapSize.x * tileSizePx.x) || 
                    y > initPos.y + (mapSize.y * tileSizePx.y));
        } 
        bool isCoordinateOutsideOfMap (sf::Vector2f position) {
            return isCoordinateOutsideOfMap (position.x, position.y);
        }
        bool isTargetBlocked (Collider& collider) {
            if (isCoordinateOutsideOfMap (collider.getPosition ()))
                return false;
           
            std::vector<sf::Vector2f> points = collider.getFourCorners ();

            if (getTileAtCoordinate (points[0])->collidable || 
                getTileAtCoordinate (points[1])->collidable || 
                getTileAtCoordinate (points[2])->collidable || 
                getTileAtCoordinate (points[3])->collidable)
                return true;
            
            return false;
        }
           
    private:
        int borderWidth = 4;
        Tile* tiles;
        sf::VertexArray mVerticies;
		sf::Texture mTexture;
		sf::Vector2i mapSize;
		sf::Vector2i tileSizePx;
		int tileWidth;
		sf::Vector2f initPos = sf::Vector2f (0.0, 0.0);
        int scale = 1;

        int size = 0;


		virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
        {
			renderStates.transform *= getTransform();
			renderStates.texture = &mTexture;
			renderTarget.draw(mVerticies, renderStates);
        }

        bool load(std::string tileset, std::string filepath, sf::Vector2i tileSize, int mapWidth, int mapHeight, sf::Vector2f position)
        {
            initPos = position;
			mapSize = sf::Vector2i(mapWidth, mapHeight);
			tileSizePx = tileSize * scale;
			
			int tileWidth = tileSizePx.x;

			if(!mTexture.loadFromFile(tileset)) //Loads TileSet texture
			{
                printf ("TileMap: Cannot open tileset\n");
				return false;
			}
			mVerticies.setPrimitiveType(sf::Quads);
			mVerticies.resize(mapWidth * mapHeight * tileWidth);




            printf ("TileMap: Populating VertexArray\n");
			for(int j = 0; j < mapHeight; j++)
			{
				for(int i = 0; i < mapWidth; i++)
				{
                    // Logic for calculating tile type on a sprite sheet

					int nTileCount = tiles[i + j * mapWidth].tileType;
                        
					int tMod = nTileCount % (mTexture.getSize().x / tileSize.x);
					int tDivd = nTileCount / (mTexture.getSize().x / tileSize.x);
                    

                    // Get the square from the vertex array
					sf::Vertex* quad = &mVerticies[(i + j * mapWidth) * tileWidth];

                    // Set the positions of the texture square
					quad[0].position = sf::Vector2f(i * tileSizePx.x + initPos.x, j *  tileSizePx.y + initPos.y); 
					quad[1].position = sf::Vector2f((i + 1) *  tileSizePx.x + initPos.x, j *  tileSizePx.y + initPos.y);
					quad[2].position = sf::Vector2f((i + 1) *  tileSizePx.x + initPos.x, (j + 1) *  tileSizePx.y + initPos.y);
					quad[3].position = sf::Vector2f(i*  tileSizePx.x + initPos.x, (j + 1) *  tileSizePx.y + initPos.y);

					quad[0].texCoords = sf::Vector2f(tMod * tileSize.x, tDivd * tileSize.y);
					quad[1].texCoords = sf::Vector2f((tMod + 1) * tileSize.x, tDivd * tileSize.y);
					quad[2].texCoords = sf::Vector2f((tMod+1) * tileSize.x, (tDivd + 1) * tileSize.y);
					quad[3].texCoords = sf::Vector2f(tMod * tileSize.x, (tDivd + 1) * tileSize.y);

				}
			}
			
			return true;
        }
		void update(int* tiles, sf::Vector2i tileIndex, sf::Vector2i tileLoc, int newTile) {
            int nTileCount = newTile;

            int tMod = nTileCount % (mTexture.getSize().x / tileSizePx.x);
            int tDivd = nTileCount / (mTexture.getSize().x / tileSizePx.x);

            sf::Vertex* quad = &mVerticies[(tileIndex.x + tileIndex.y * mapSize.x) * tileWidth];

            quad[0].position = sf::Vector2f(tileIndex.x * tileSizePx.x + initPos.x, tileIndex.y * tileSizePx.y + initPos.y);
            quad[1].position = sf::Vector2f((tileIndex.x + 1) * tileSizePx.x + initPos.x, tileIndex.y * tileSizePx.y + initPos.y);
            quad[2].position = sf::Vector2f((tileIndex.x + 1) * tileSizePx.x + initPos.x, (tileIndex.y + 1) * tileSizePx.y + initPos.y);
            quad[3].position = sf::Vector2f(tileIndex.x * tileSizePx.x + initPos.x, (tileIndex.y + 1) * tileSizePx.y + initPos.y);

            quad[0].texCoords = sf::Vector2f(tMod * tileSizePx.x, tDivd * tileSizePx.y);
            quad[1].texCoords = sf::Vector2f((tMod + 1) * tileSizePx.x, tDivd * tileSizePx.y);
            quad[2].texCoords = sf::Vector2f((tMod+1) * tileSizePx.x, (tDivd + 1) * tileSizePx.y);
            quad[3].texCoords = sf::Vector2f(tMod * tileSizePx.x, (tDivd + 1) * tileSizePx.y);
        }
        
};