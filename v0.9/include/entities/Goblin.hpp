#include "Monster.hpp"

// Goblin class
class Goblin : public Monster {

    public:

        Goblin(const int lv) : Monster("assets/entities/monsters/goblin.png", TILE_SIZE, TILE_SIZE, lv) 
        {
            buildMonster();
        }

        void buildMonster() override {
            totalHealth = 15.f + (level-1) * 0.45f; // level 100 => 60.00
            currentHealth = totalHealth;
            power = 4.f + (level-1) * 0.11f; // level 100 => 15.00
            speed = 6.f + (level -1) * 0.04f; // level 100 => 10.00
        }
};
