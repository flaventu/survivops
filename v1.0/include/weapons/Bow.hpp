#include "Weapon.hpp"

class Bow : public Weapon {

    public:
        Bow() : Weapon("assets/weapons/bow.png", "Bow", 10, TILE_SIZE * 1.4, 800) {}

        void updateStats() override {
            damage += 2.5f; // level 5 => 20.00
            cooldown -= 50; // level 5 => 500
            range += TILE_SIZE * 0.2f; // level 5 => 2.2 tiles
        }
};
