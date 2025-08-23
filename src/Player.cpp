#include "../include/Player.hpp"
using namespace sf;


Player::Player() : Entity("assets/entity/player/spritesheet.png", TILE_SIZE, TILE_SIZE)
{

    position = {0, 0}; // Initialize the position of the player sprite
    speed = 3; // Set the speed of the player sprite

    entitySprite.setOrigin({TILE_SIZE / 2.0f, TILE_SIZE / 2.0f}); // Set the origin of the player sprite to the center
    entitySprite.setPosition(position); // Set the initial position of the player sprite

    entityHitbox.setSize({HITBOX_SIZE,HITBOX_SIZE}); // Set the size of the player hitbox
    entityHitbox.setOrigin({HITBOX_SIZE / 2.0f, HITBOX_SIZE / 2.0f}); // Set the origin of the player hitbox to the center
    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the initial position of the player hitbox
}

void Player::gainExp(const float exp) {
    currentExp += exp;
    if(currentExp >= expForNew) {
        currentExp -= expForNew;
        level++;
        upgradePlayer();
    }
}

void Player::upgradePlayer() {
    totalHealth += 0.8f;
    speed += 0.03f;
    power += 0.015f;
    dodge += 0.2f;
    expForNew = level * 100.f;
}