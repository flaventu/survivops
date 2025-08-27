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

void Player::update(const DIRECTIONS dir, const Collision& collision, const std::vector<std::unique_ptr<Npc>>& npc_entities)
{

    Vector2f newPosition = position;

    switch (dir)
    {
        case UP: newPosition.y -= speed; break;
        case DOWN: newPosition.y += speed; break;
        case LEFT: newPosition.x -= speed; break;
        case RIGHT: newPosition.x += speed; break;
        default: break;
    }

    direction = dir;

    for (const auto& npc : npc_entities) {
        if (npc->isVisible() && collision.collision(entityHitbox.getGlobalBounds(), direction, speed, *npc)) {
            dialogueActive = true;
            currentNpc = npc.get();
            npc->startDialogue();
            return;
        }
    }

    dialogueActive = false;
    currentNpc = nullptr;

    if(!collision.collision(entityHitbox.getGlobalBounds(), direction, speed))
    {
        position = newPosition; // Update the position if there is no collision

        animate();
    }

    // Update the entity sprite position
    entitySprite.setPosition(position);
    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the position of the entity hitbox
    updateTextureRect();
}