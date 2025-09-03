#include "../../include/entities/Witch.hpp"
#include "../../include/entities/Player.hpp"


void Witch::attack(Player& target) {
    if(rand() % 100 < target.getDodge()) return; // target dodges the attack
    target.takeDamage(power);

    // Random poisoning effect
    if (rand() % 100 < 20 + level) // 20% + level chance to inflict poison
        target.getPoisoned(power);
}
