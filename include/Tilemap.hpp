#pragma once
#include "const.hpp"
#include "entities/Goblin.hpp"
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

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

        // Monster spawning
        const bool fightable;
        sf::Clock spawnMonsterClock;
        static constexpr int MAX_MONSTERS = 15;

        void spawnEntity(Entity&);

        void draw(sf::RenderTarget&, sf::RenderStates) const override;
        
    public:

        TileMap(const std::filesystem::path&, const std::filesystem::path&, const int, const bool); 

        sf::Vector2i positionToTile(const sf::Vector2f& position) const {
            return {
                static_cast<int>(std::floor((position.x + mapSize.x / 2.f) / TILE_SIZE)),
                static_cast<int>(std::floor((position.y + mapSize.y / 2.f) / TILE_SIZE))
            };
        }

        std::vector<std::shared_ptr<Entity>> entities = {};

        void loadNpcs(const std::vector<std::shared_ptr<Entity>>& npcs) {
            entities = npcs;
            for (const auto& npc : entities) {
                spawnEntity(*npc);
            }
        }

        // Getters
        const int getWidth() const { return width; }
        const int getHeight() const { return height; }
        const sf::Vector2u& getMapSize() const { return mapSize; }
        const bool isFightable() const { return fightable; }

        bool isSolid(const sf::Vector2i& tileNum) const { return m_tiles[tileNum.x][tileNum.y] >= solidTileNum; } 

        void spawnMonster();

        void update(const sf::View&);
};
