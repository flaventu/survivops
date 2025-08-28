#include "Weapon.hpp"

class Hand : public Weapon {

    public:

        Hand() : Weapon("assets/weapons/hand.png", 1, TILE_SIZE/2, 100) {}

        void updateStats() override {}

};