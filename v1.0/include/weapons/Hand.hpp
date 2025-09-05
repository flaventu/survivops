#include "Weapon.hpp"

class Hand : public Weapon {

    public:

        Hand() : Weapon("assets/weapons/hand.png", "Hand", 5, TILE_SIZE, 100) {}

        void updateStats() override {
            damage += 1.25f; // level 5 => 10.00
            cooldown -= 10; // level 5 => 60
            range += TILE_SIZE * 0.125f; // level 5 => 1.5 tiles
        }

};