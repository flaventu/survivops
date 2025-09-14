#include "Weapon.hpp"

class Sword : public Weapon {

    public:
        Sword() : Weapon("assets/weapons/sword.png", "Sword", 8, TILE_SIZE * 1.15f, 400.f) {}

        void updateStats() override {
            damage += 2.f; // level 5 => 16.00
            cooldown -= 25; // level 5 => 300
            range += TILE_SIZE * 0.15f; // level 5 => 1.6 tiles
        }
};
