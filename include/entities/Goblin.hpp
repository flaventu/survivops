#include "Monster.hpp"

// Goblin class
class Goblin : public Monster {

    public:
        Goblin() : Monster("assets/entities/monsters/goblin.png", TILE_SIZE, TILE_SIZE) 
        {
            // Initialize Goblin-specific attributes
            power = 4.f;
            speed = 5.f;
            totalHealth = 15.f;
            currentHealth = totalHealth;
        }

        // Monster state
        void upgradeMonster() override {
            level++;
            totalHealth += 10;
            currentHealth = totalHealth;
            power += 2;
            speed += 1;
        }
};
