#pragma once
#include "Tilemap.hpp"
#include "Entity.hpp"

// Collision detection class
class Collision {

    private:

        TileMap& tilemap;

    public:

        Collision(TileMap& tilemap) : tilemap(tilemap) {}

        bool collision(const sf::FloatRect&, const DIRECTIONS, const float) const;
        bool collision(const sf::FloatRect&, const DIRECTIONS, const float, const Entity&) const;
        bool collision(const sf::FloatRect&, const DIRECTIONS, const float, const sf::FloatRect&) const;

};
