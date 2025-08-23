#pragma once
#include "const.hpp"
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{

    private:

        sf::VertexArray m_vertices; // Vertex array to hold the tile vertices
        sf::Texture m_tileset; // Texture for the tileset
        std::vector<std::vector<int>> m_tiles; // 2D vector to hold the tile data
        unsigned int width, height; // Width and height of the map in tiles
        sf::Vector2f mapSize; // Size of the map in pixels
        int solidTileNum; // Tile number for solid tiles (grather or equal than solidTileNum are solid tiles)
        
        bool loadMapFromCSV(const std::filesystem::path&); // Function to load the map from a CSV file
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool isSolid(const int tileNum) const { return tileNum >= solidTileNum; } // Function to check if a tile is solid
        
        public:
        
        bool load(const std::filesystem::path&, const std::filesystem::path&, const int); // Function to load the map from a file
        void update(const sf::View&); // Function to update the tilemap based on the view
        bool collision(const sf::FloatRect&, const DIRECTIONS, const float); // Function to check for collisions with a hitbox
};
