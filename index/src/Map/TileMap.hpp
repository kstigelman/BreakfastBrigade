#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        TileMap (int width, int height) {
            size = width * height;
            mapSize = sf::Vector2i (width, height);
            tiles = new Tile[width * height];
            Tile tile;
            for (size_t j = 0; j < height; ++j) {
                for (size_t i = 0; i < width; ++i) {
                    tile.position = sf::Vector2i (i, j);
                    tile.tilePosition = sf::Vector2f (i * tileWidth, j * tileWidth);
                    
                    if (i < borderWidth || i > width - borderWidth - 1 || j < borderWidth || j > height - borderWidth - 1) {
                        tile.collidable = true;
                        tile.tileType = 1;
                    }
                    tiles[i + (j * width)] = tile;
                }
            }
            load ("resources/sprites/Tiles.png", "N/A", sf::Vector2i (32, 32), width, height, sf::Vector2f (0, 0));
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

        }
        Tile* getAtCoordinate (int x, int y) {
            sf::Vector2i castCoordinates = sf::Vector2i (x % tileSizePx.x, y % tileSizePx.y);
            return &tiles[x + (y * mapSize.x)];
        }   
    private:
        int borderWidth = 4;
        Tile* tiles;
        sf::VertexArray mVerticies;
		sf::Texture mTexture;
		sf::Vector2i mapSize;
		sf::Vector2i tileSizePx;
		int tileWidth;
		sf::Vector2f initPos;
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
				return false;
			}
			mVerticies.setPrimitiveType(sf::Quads);
			mVerticies.resize(mapWidth * mapHeight * tileWidth);

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