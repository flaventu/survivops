#include "Monster.hpp"

// Goblin class
class Goblin : public Monster {

    public:
        Goblin() : Monster("assets/entities/monsters/goblin.png", TILE_SIZE, TILE_SIZE, 15.f, 5.f, 5.f) {}

        // Monster state
        void upgradeMonster() override {
            level++;
            totalHealth += 10;
            currentHealth = totalHealth;
            power += 2;
            speed += 1;
        }
};
