#include "Entity.hpp"

class Monster : public Entity {

    protected:

        // Attributes
        int level = 1;
        float power;

        // Animation
        sf::Clock animationClock;
        void animate() override {}
    
    public:

    Monster(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const float health, const float power, const float sp)
        : Entity(textureFile, frameWidth, frameHeight), power(power) 
        {
            totalHealth = health;
            currentHealth = totalHealth;
            speed = sp;
        }

    // Getters
    const float getPower() const { return power; };

    void attack(Entity& target) {
        target.takeDamage(power);
    }

    void followPlayer(const sf::Vector2i& tilePosition) {}

    // Monster state
    virtual void upgradeMonster() = 0;

    void update(const sf::Vector2i& playerPosition, const sf::View& view) {
        followPlayer(playerPosition);
        entitySprite.setPosition(position);
        updateVisibility(view);
    }
};
