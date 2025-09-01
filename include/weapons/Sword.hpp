#include "Weapon.hpp"

class Sword : public Weapon {

    public:
        Sword() : Weapon("assets/weapons/sword.png", "Sword", 8, TILE_SIZE * 0.75, 500) {}

        void updateStats() override {
            damage += 1.5f;
            cooldown -= 20;
            range += TILE_SIZE / 4;
        }
};
