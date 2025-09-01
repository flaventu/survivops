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
        void animate() override { spriteNum = (spriteNum + 1) % 2; }
    
    public:

    Monster(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const float health, const float power, const float sp)
        : Entity(textureFile, frameWidth, frameHeight), power(power), moveClock(), animationClock()
        {
            totalHealth = health;
            currentHealth = totalHealth;
            speed = sp;
        }

    // Getters
    const float getPower() const { return power; };

    void attack(Player& target);

    void followPlayer(const sf::Vector2i& tilePosition) {}

    // Monster state
    virtual void upgradeMonster() = 0;

    void update(const sf::Vector2i&, const sf::View&, const TileMap&, const Collision&, Player&);
};
