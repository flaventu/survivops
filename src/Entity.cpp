#include "../include/Entity.hpp"
using namespace sf;

void Entity::updateTextureRect() {

    sf::IntRect rect;
    rect.position.x = spriteNum * frameWidth;
    rect.position.y = direction * frameHeight;
    rect.size.x = frameWidth;
    rect.size.y = frameHeight;

    entitySprite.setTextureRect(rect);
}

void Entity::update(const DIRECTIONS dir, TileMap& tilemap, Clock& clock)
{
    Vector2f newPosition = position; // Create a new position vector to store the updated position

    // Update the direction and position based on the input
    switch (dir)
    {
        case UP:
            direction = UP;
            newPosition.y -= speed;
            break;
        case DOWN:
            direction = DOWN;
            newPosition.y += speed;
            break;
        case LEFT:
            direction = LEFT;
            newPosition.x -= speed;
            break;
        case RIGHT:
            direction = RIGHT;
            newPosition.x += speed;
            break;
    }

    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the position of the entity hitbox

    if(!tilemap.collision(entityHitbox.getGlobalBounds(), direction, speed))
    {
        position = newPosition; // Update the position if there is no collision

        // update the sprite animation every 200 milliseconds (12 frames at 60 FPS)
        if(clock.getElapsedTime().asMilliseconds() > 200) {
            spriteNum = (spriteNum + 1) % 2; // Toggle between spriteNum 0 and 1
            clock.restart();
        }
    }

    // Update the entity sprite position
    entitySprite.setPosition(position);
    updateTextureRect();
}