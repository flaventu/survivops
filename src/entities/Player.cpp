#include "../../include/entities/Player.hpp"
using namespace sf;
using namespace std;

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

void Player::update(const DIRECTIONS dir, const Collision& collision, const vector<shared_ptr<Entity>>& entities)
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

    for (const auto& entity : entities) {

        
        if (entity->isVisible() && collision.collision(getHitbox(), direction, speed, entity->getHitbox())) {

            // If the entity is an NPC, we can start a dialogue
            if(Npc* npc = dynamic_cast<Npc*>(entity.get())) {
                dialogueActive = true;
                currentNpc = npc;
                npc->startDialogue();
                return;
            }
            // else monster part
            else {
                Monster& monster = dynamic_cast<Monster&>(*entity.get());
                takeDamage(monster.getPower());
                return;
            }
        }
    }

    // reset dialogue
    dialogueActive = false;
    currentNpc = nullptr;

    // Check for collisions with the environment
    if(!collision.collision(getHitbox(), direction, speed))
    {
        position = newPosition; // Update the position if there is no collision

        animate();
    }

    // Update the entity sprite position and hitbox
    entitySprite.setPosition(position);
    entityHitbox.position = {position.x - (HITBOX_SIZE / 2), position.y - (HITBOX_SIZE / 2) + HITBOX_OFFSET}; // Set the position of the entity hitbox
    updateTextureRect();
}

bool Player::attack(const Collision& collision, const std::vector<std::shared_ptr<Entity>>& monsters) {

    
    if (weapon->isUsable()) {

        weapon->useWeapon();

        Vector2f attackPosition;

        switch (direction)
        {
        case UP:
            attackPosition = {position.x, position.y - weapon->getRange()};
            break;

        case DOWN:
            attackPosition = {position.x, position.y + weapon->getRange()};
            break;

        case LEFT:
            attackPosition = {position.x - weapon->getRange(), position.y};
            break;

        case RIGHT:
            attackPosition = {position.x + weapon->getRange(), position.y};
            break;
        }

        for(auto& monster : monsters) {
            if(monster->isVisible() && collision.collision(attackPosition, monster->getHitbox())) {
                monster->takeDamage(weapon->getDamage());
            }
        }
        return true;
    }
    return false;
}
