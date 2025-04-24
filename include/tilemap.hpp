#pragma once
#include "const.hpp"
#include "object.hpp" 
#include <vector>

// typedef std::vector<std::vector<int>> MapData; // Type alias for 2D vector of integerss

class TileMap : public sf::Drawable, public sf::Transformable
{

    private:

        sf::VertexArray m_vertices; // Vertex array to hold the tile vertices
        sf::Texture m_tileset; // Texture for the tileset
        std::vector<std::vector<int>> m_tiles; // 2D vector to hold the tile data
        unsigned int width, height; // Width and height of the map in tiles
        sf::Vector2f mapSize; // Size of the map in pixels
        int solidTileNum; // Tile number for solid tiles (grather or equal than solidTileNum are solid tiles)
        std::vector<Object*> m_objects; // Vector to hold objects in the map
        
        bool loadMapFromCSV(const std::filesystem::path&); // Function to load the map from a CSV file

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:

        bool load(const std::filesystem::path&, const std::filesystem::path&, const int); // Function to load the map from a file
        void update(const sf::View&); // Function to update the tilemap based on the view
        bool isSolid(int tileNum) const { return tileNum >= solidTileNum; } // Function to check if a tile is solid
        bool collision(const sf::FloatRect&, const DIRECTIONS, float) const; // Function to check for collisions with a hitbox
        bool loadObjects(const std::filesystem::path&); // Function to load objects from a file
        void drawObjects(sf::RenderTarget& target) const; // Function to draw objects on the map
        bool containsObjects(sf::Vector2i tileNum) const; // Function to check if a tile contains objects
};
