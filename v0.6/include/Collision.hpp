#pragma once
#include "Tilemap.hpp"

// Collision detection class
class Collision {

    private:

        TileMap& tilemap;

    public:

        Collision(TileMap& tilemap) : tilemap(tilemap) {}

        bool checkTileCollision(const sf::FloatRect&, const DIRECTIONS, const float) const;

};
