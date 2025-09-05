#include "Monster.hpp"

// Knight class
class Knight : public Monster {

    public:

        Knight(const int lv) : Monster("assets/entities/monsters/knight.png", TILE_SIZE, TILE_SIZE, lv) 
        {
            buildMonster();
        }

        void buildMonster() override {
            totalHealth = 30.f + (level-1) * 0.9f; // level 100 => 120.00
            currentHealth = totalHealth;
            power = 8.f + (level-1) * 0.22f; // level 100 => 30.00
            speed = 3.f + (level -1) * 0.03f; // level 100 => 6.00
        }
};
