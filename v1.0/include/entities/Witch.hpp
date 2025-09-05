#pragma once
#include "Monster.hpp"

// Witch class
class Witch : public Monster {

    public:

        Witch(const int lv) : Monster("assets/entities/monsters/witch.png", TILE_SIZE, TILE_SIZE, lv) 
        {
            buildMonster();
        }

        void buildMonster() override {
            totalHealth = 10.f + (level-1) * 0.35f; // level 100 => 45.00
            currentHealth = totalHealth;
            power = 2.f + (level-1) * 0.06f; // level 100 => 8.00
            speed = 5.f + (level -1) * 0.03f; // level 100 => 8.00
        }

        void attack(Player& target) override;
};
