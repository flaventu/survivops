#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

typedef std::vector<std::vector<int>> MapData; // Type alias for 2D vector of integers

class TileMap : public sf::Drawable, public sf::Transformable
{

    private:

        sf::VertexArray m_vertices; // Vertex array to hold the tile vertices
        sf::Texture m_tileset; // Texture for the tileset
        MapData m_tiles; // 2D vector to hold the tile data
        unsigned int width, height; // Width and height of the map in tiles
        sf::Vector2f mapSize; // Size of the map in pixels
        
        bool loadMapFromCSV(const std::filesystem::path&); // Function to load the map from a CSV file

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:

        bool load(const std::filesystem::path&, const std::filesystem::path&); // Function to load the map from a file
        void update(const sf::View&); // Function to update the tilemap based on the view
   
};
