#pragma once
#include "Entity.hpp"

// Class to handle the player character
class Player : public Entity
{
    private:

        // Attributes
        int level = 1;
        float totalHealth = 20.f;
        float currentHealth = totalHealth;
        float power = 5.f;
        float dodge = 5.f; // %

        int money = 0;
        float expForNew = level * 100;
        float currentExp = 0;

        sf::Clock animationClock;

        void animate() override;

    public:

        Player() : Entity("assets/entities/player/spritesheet.png", TILE_SIZE, TILE_SIZE), animationClock()
        { position = {0, 0}; speed = 3; }

        // Getters
        const float getHealth() const { return currentHealth; };
        const int getMoney() const { return money; };
        
        // Setters
        void gainMoney(const int coins) { money += coins; };
        void gainExp(const float);
        void heal(const float heal) { currentHealth += heal; if(currentHealth > totalHealth) currentHealth = totalHealth; };
        void takeDamage(const float damage) { currentHealth -= damage; if(currentHealth < 0) currentHealth = 0; };

        // Player state
        void upgradePlayer();
        void respawn() { currentHealth = totalHealth; position = {0, 0}; };
        
        // UI utils
        const int getCurrentLevel() const { return level; };
        const float getExpPerc() const { return currentExp/expForNew; };
        const float getHealthPerc() const { return currentHealth / totalHealth; };
};
