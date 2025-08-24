#pragma once
#include "const.hpp"
#include <vector>

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

        sf::Vector2f lastPosition = {0, -1};

        static const int maxVertexCount = (MAX_SCREEN_COLS+1) * (MAX_SCREEN_ROWS+1) * 6;

        bool loadMapFromCSV(const std::filesystem::path&);
        
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        
    public:
        
        TileMap(const std::filesystem::path&, const std::filesystem::path&, const int); 

        bool isSolid(const int tileNum) const { return tileNum >= solidTileNum; } 
        
        void update(const sf::View&);

        bool collision(const sf::FloatRect&, const DIRECTIONS, const float);
};
