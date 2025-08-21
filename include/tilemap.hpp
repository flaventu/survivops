#pragma once
#include "const.hpp"
#include "Object.hpp" 
#include <vector>
#include <unordered_map>


#include <utility> // std::pair
#include <functional> // std::hash

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // Combina gli hash
    }
};

class TileMap : public sf::Drawable, public sf::Transformable
{

    private:

        sf::VertexArray m_vertices; // Vertex array to hold the tile vertices
        sf::Texture m_tileset; // Texture for the tileset
        std::vector<std::vector<int>> m_tiles; // 2D vector to hold the tile data
        unsigned int width, height; // Width and height of the map in tiles
        sf::Vector2f mapSize; // Size of the map in pixels
        int solidTileNum; // Tile number for solid tiles (grather or equal than solidTileNum are solid tiles)
        std::unordered_map<std::pair<int,int>, Object*, pair_hash> m_objects; // Vector to hold objects in the map
        
        bool loadMapFromCSV(const std::filesystem::path&); // Function to load the map from a CSV file
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool containsObjects(const sf::Vector2i tileNum) const { return m_objects.find({tileNum.x, tileNum.y}) != m_objects.end();}
        void drawObjects(sf::RenderTarget&) const; // Function to draw objects on the map
        bool isSolid(const int tileNum) const { return tileNum >= solidTileNum; } // Function to check if a tile is solid
        void visibleObjects(const sf::Vector2i) const; // Function to check if a tile has objects
        void pickObject(const sf::Vector2i tileNum); // Function to pick objects from a tile
        
        public:

        std::vector<Object*> pickableObjects; // Vector to hold pickable objects
        
        bool load(const std::filesystem::path&, const std::filesystem::path&, const int); // Function to load the map from a file
        bool loadObjects(const std::filesystem::path&); // Function to load objects from a file
        void update(const sf::View&); // Function to update the tilemap based on the view
        bool collision(const sf::FloatRect&, const DIRECTIONS, const float); // Function to check for collisions with a hitbox
};
