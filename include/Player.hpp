#pragma once
#include "Entity.hpp"
#include "Object.hpp"
#include <set>

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

        std::set<Object*> inventory; // Set to hold the player's inventory
        int money = 0;
        float expForNew = level * 100;
        float currentExp = 0;

    public:

        Player(); // Constructor to initialize the player sprite

        void addToInventory(Object* object) { if(inventory.size() <= 4) inventory.insert(object); } // Add an object to the inventory
        void removeFromInventory(Object* object) { inventory.erase(object); } // Remove an object from the inventory
        bool hasObject(Object* object) const { return inventory.find(object) != inventory.end(); } // Check if the player has an object in the inventory
        void clearInventory() { inventory.clear(); } // Clear the inventory
        float getExpPerc() const { return currentExp/expForNew; };
        int getCurrentLevel() const { return level; };
        int getMoney() const { return money; };
        void gainMoney(const int coins) { money += coins; };
        void gainExp(const float);
        std::set<Object*> getInventory() const { return inventory; };
        void upgradePlayer();
        void heal(const float heal) { currentHealth += heal; if(currentHealth > totalHealth) currentHealth = totalHealth; };
        void takeDamage(const float damage) { currentHealth -= damage; if(currentHealth < 0) currentHealth = 0; };
        void respawn() { currentHealth = totalHealth; position = {0, 0}; };

        float getHealth() const { return currentHealth; };
        float getHealthPerc() const { return currentHealth / totalHealth; };
};
