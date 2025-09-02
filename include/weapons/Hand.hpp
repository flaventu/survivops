#include "Weapon.hpp"

class Hand : public Weapon {

    public:

        Hand() : Weapon("assets/weapons/hand.png", "Hand", 5, TILE_SIZE, 100) {}

        void updateStats() override {
            damage += 1.f;
            cooldown -= 10;
            range += TILE_SIZE / 4;
        }

};