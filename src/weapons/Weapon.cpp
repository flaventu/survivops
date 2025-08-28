#include "../../include/weapons/Weapon.hpp"

// Can only be called when usable is true
void Weapon::useWeapon() {

    // set non-usable texture, make usable false and restart the clock
    weaponSprite.setTextureRect(sf::IntRect({weaponSprite.getTextureRect().position.x - TILE_SIZE, weaponSprite.getTextureRect().position.y}, {TILE_SIZE, TILE_SIZE}));
    usable = false;
    cooldownClock.restart();
}

void Weapon::update() {
    if (!usable && cooldownClock.getElapsedTime().asMilliseconds() >= cooldown) {
        usable = true;
    }
}