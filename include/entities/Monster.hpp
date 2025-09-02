#pragma once
#include "Entity.hpp"
#include "../Pathfinding.hpp"

class TileMap; class Player; class Collision; // forward declarations to avoid circular dependencies
class Monster : public Entity {

    protected:

        // Attributes
        int level;
        float power;

        // Animation
        sf::Clock moveClock;
        sf::Clock pathClock;
        sf::Font levelFont;
        sf::Text levelText;
        sf::RectangleShape healthBar;
        sf::RectangleShape healthBarBack;

        std::vector<sf::Vector2i> path = {};

    public:

        Monster(const std::filesystem::path&, const int, const int, const int);

        // Getters
        const float getPower() const { return power; };
        const int getLevel() const { return level; };

        virtual void attack(Player& target);

        // Monster state
        virtual void buildMonster() = 0;

        void updateUI();

        void update(const sf::Vector2i&, const sf::View&, const TileMap&, const Collision&, Player&);
        void draw(sf::RenderWindow& window) const override;
    };
