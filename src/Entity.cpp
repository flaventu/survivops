#include "../include/Entity.hpp"
using namespace sf;

void Entity::updateTextureRect() {

    IntRect rect;
    rect.position.x = spriteNum * frameWidth;
    rect.position.y = direction * frameHeight;
    rect.size.x = frameWidth;
    rect.size.y = frameHeight;

    entitySprite.setTextureRect(rect);
}

void Entity::update(const DIRECTIONS dir, TileMap& tilemap)
{

    Vector2f newPosition = position; // Create a new position vector to store the updated position

    // Update the temporary position based on the input
    switch (dir)
    {
        case UP:
            newPosition.y -= speed;
            break;
        case DOWN:
            newPosition.y += speed;
            break;
        case LEFT:
            newPosition.x -= speed;
            break;
        case RIGHT:
            newPosition.x += speed;
        break;
    }

    direction = dir;

    if(!tilemap.collision(entityHitbox.getGlobalBounds(), direction, speed))
    {
        position = newPosition; // Update the position if there is no collision

        // update the sprite animation every 200 milliseconds (12 frames at 60 FPS)
        if(animationClock.getElapsedTime().asMilliseconds() > 200) {
            spriteNum = (spriteNum + 1) % 2; // Toggle between spriteNum 0 and 1
            animationClock.restart();
        }
    }

    // Update the entity sprite position
    entitySprite.setPosition(position);
    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the position of the entity hitbox
    updateTextureRect();
}