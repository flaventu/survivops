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

    public:

        Player(); // Constructor to initialize the player sprite

        // Getters
        float getHealth() const { return currentHealth; };
        int getMoney() const { return money; };
        
        // Setters
        void gainMoney(const int coins) { money += coins; };
        void gainExp(const float);
        void heal(const float heal) { currentHealth += heal; if(currentHealth > totalHealth) currentHealth = totalHealth; };
        void takeDamage(const float damage) { currentHealth -= damage; if(currentHealth < 0) currentHealth = 0; };

        // Player state
        void upgradePlayer();
        void respawn() { currentHealth = totalHealth; position = {0, 0}; };
        
        // UI utils
        int getCurrentLevel() const { return level; };
        float getExpPerc() const { return currentExp/expForNew; };
        float getHealthPerc() const { return currentHealth / totalHealth; };
};
