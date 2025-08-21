#pragma once
#include "Entity.hpp"
#include "Object.hpp"
#include <set>

// Class to handle the player character
class Player : public Entity
{
    private:

        std::set<Object*> inventory; // Set to hold the player's inventory
        int money = 0;
        int level = 1;
        float expForNew = level * 100;
        float currentExp = 0;
        void loadTextures() override; // Load textures for the player sprite

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
};
