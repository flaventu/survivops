#include "../include/entities/Player.hpp"
using namespace sf;


Player::Player() : Entity("assets/entities/player/spritesheet.png", TILE_SIZE, TILE_SIZE)
{

    position = {0, 0};
    speed = 3; 

    entitySprite.setOrigin({TILE_SIZE / 2.0f, TILE_SIZE / 2.0f});
    entitySprite.setPosition(position);

    entityHitbox.setSize({HITBOX_SIZE,HITBOX_SIZE});
    entityHitbox.setOrigin({HITBOX_SIZE / 2.0f, HITBOX_SIZE / 2.0f});
    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET});
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