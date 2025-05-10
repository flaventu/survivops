#pragma once
#include "entity.hpp"
#include "object.hpp"
#include <set>

// Class to handle the player character
class Player : public Entity
{
    private:

        std::set<Object*> inventory; // Set to hold the player's inventory
        void loadTextures() override; // Load textures for the player sprite

    public:

        Player(); // Constructor to initialize the player sprite

        void addToInventory(Object* object) { inventory.insert(object); } // Add an object to the inventory
        void removeFromInventory(Object* object) { inventory.erase(object); } // Remove an object from the inventory
        bool hasObject(Object* object) const { return inventory.find(object) != inventory.end(); } // Check if the player has an object in the inventory
        void clearInventory() { inventory.clear(); } // Clear the inventory
};
