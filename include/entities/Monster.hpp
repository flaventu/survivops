#pragma once
#include "Entity.hpp"

class TileMap; class Player; class Collision; // forward declarations
class Monster : public Entity {

    protected:

        // Attributes
        int level = 1;
        float power;

        // Animation
        sf::Clock animationClock;
        sf::Clock moveClock;
        sf::Font levelFont;
        sf::Text levelText;
        sf::RectangleShape healthBar;
        sf::RectangleShape healthBarBack;
        void animate() override { spriteNum = (spriteNum + 1) % 2; }
    
    public:

    Monster(const std::filesystem::path&, const int, const int);

    // Getters
    const float getPower() const { return power; };
    const int getLevel() const { return level; };

    void attack(Player& target);

    void followPlayer(const sf::Vector2i& tilePosition) {}

    // Monster state
    virtual void upgradeMonster() = 0;

    void updateUI();

    void update(const sf::Vector2i&, const sf::View&, const TileMap&, const Collision&, Player&);
    void draw(sf::RenderWindow& window) const override;
};
