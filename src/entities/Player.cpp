#include "../include/entities/Player.hpp"
using namespace sf;

void Player::animate()
{
    // update the sprite animation every 200 milliseconds (12 frames at 60 FPS)
    if(animationClock.getElapsedTime().asMilliseconds() > 200) {
        spriteNum = (spriteNum + 1) % 2; // Toggle between spriteNum 0 and 1
        animationClock.restart();
    }
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