#pragma once
#include "Tilemap.hpp"

// Collision detection class
class Collision {

    private:

        TileMap& tilemap;

    public:

        Collision(TileMap& tilemap) : tilemap(tilemap) {}

        bool collision(const sf::FloatRect&, const DIRECTIONS, const float) const; // Entity on Tilemap
        bool collision(const sf::FloatRect&, const DIRECTIONS, const float, const sf::FloatRect&) const; // Entity on Entity

};
