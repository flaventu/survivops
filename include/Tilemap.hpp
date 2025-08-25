#pragma once
#include "const.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

class TileMap : public sf::Drawable, public sf::Transformable
{

    private:

        // Vertex array to hold the tile vertices
        sf::VertexArray m_vertices;

        // Map data
        const sf::Texture m_tileset;
        std::vector<std::vector<int>> m_tiles;
        int width, height;
        sf::Vector2u mapSize;
        const int solidTileNum; // grather or equal than solidTileNum are solid tiles

        static const int maxVertexCount = (MAX_SCREEN_COLS+1) * (MAX_SCREEN_ROWS+1) * 6;

        bool loadMapFromCSV(const std::filesystem::path&);
        
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        
    public:
        
        TileMap(const std::filesystem::path&, const std::filesystem::path&, const int); 

        sf::Vector2i positionToTile(const sf::Vector2f& position) const {
            return {
                static_cast<int>(std::floor((position.x + mapSize.x / 2.f) / TILE_SIZE)),
                static_cast<int>(std::floor((position.y + mapSize.y / 2.f) / TILE_SIZE))
            };
        }

        // Getters
        const int getWidth() const { return width; }
        const int getHeight() const { return height; }
        const sf::Vector2u& getMapSize() const { return mapSize; }

        bool isSolid(const sf::Vector2i& tileNum) const { return m_tiles[tileNum.x][tileNum.y] >= solidTileNum; } 

        void update(const sf::View&);
};
