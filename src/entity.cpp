#include "../include/entity.hpp"
using namespace sf;

void Entity::update(const DIRECTIONS dir, const TileMap& tilemap)
{
    Vector2f newPosition = position; // Create a new position vector to store the updated position
    switch (dir)
    {
        case UP:
            direction = UP; // Set the direction to UP
            newPosition.y -= speed; // Move the sprite up
            if(spriteNum == 1)
                currentTexture = &up1; // Set the texture to up1
            else
                currentTexture = &up2; // Set the texture to up2
            break;
        case DOWN:
            direction = DOWN; // Set the direction to DOWN
            newPosition.y += speed; // Move the sprite down
            if(spriteNum == 1)
                currentTexture = &down1; // Set the texture to down1
            else
                currentTexture = &down2; // Set the texture to down2
            break;
        case LEFT:
            direction = LEFT; // Set the direction to LEFT
            newPosition.x -= speed; // Move the sprite left
            if(spriteNum == 1)
                currentTexture = &left1; // Set the texture to left1
            else
                currentTexture = &left2; // Set the texture to left2
            break;
        case RIGHT:
            direction = RIGHT; // Set the direction to RIGHT
            newPosition.x += speed; // Move the sprite right
            if(spriteNum == 1)
                currentTexture = &right1; // Set the texture to right1
            else
                currentTexture = &right2; // Set the texture to right2
            break;
    }

    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the position of the entity hitbox

    if(!tilemap.collision(entityHitbox.getGlobalBounds(), direction, speed))
    {
        position = newPosition; // Update the position if there is no collision
        // change the sprite texture for animation every 12 frames
        spriteCount++; 
        if (spriteCount > 12)
        {
            spriteCount = 0; // Reset the sprite count
            spriteNum = (spriteNum == 1) ? 2 : 1; // Toggle between spriteNum 1 and 2 for animation
        }
    }

    // Update the entity sprite position
    entitySprite.setPosition(position); // Set the position of the entity sprite
    entitySprite.setTexture(currentTexture); // Set the texture of the entity sprite
}