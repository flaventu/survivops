#include "../include/player.hpp"
using namespace sf;


void Player::loadTextures() 
{
    // Load the textures for the player sprite
    if (!up1.loadFromFile("assets/entity/player/up1.png")) throw Exception("Failed to load up1 texture");
    if (!up2.loadFromFile("assets/entity/player/up2.png")) throw Exception("Failed to load up2 texture");
    if (!down1.loadFromFile("assets/entity/player/down1.png")) throw Exception("Failed to load down1 texture");
    if (!down2.loadFromFile("assets/entity/player/down2.png")) throw Exception("Failed to load down2 texture");
    if (!left1.loadFromFile("assets/entity/player/left1.png")) throw Exception("Failed to load left1 texture");
    if (!left2.loadFromFile("assets/entity/player/left2.png")) throw Exception("Failed to load left2 texture");
    if (!right1.loadFromFile("assets/entity/player/right1.png")) throw Exception("Failed to load right1 texture");
    if (!right2.loadFromFile("assets/entity/player/right2.png")) throw Exception("Failed to load right2 texture");
}


Player::Player()
{
    // Load the textures for the player sprite
    try {
        loadTextures(); 
    } catch (const Exception& e) {
        throw e; // Throw the exception if there is an error loading textures
    }
    playerSprite.setSize({TILE_SIZE, TILE_SIZE}); // Set the size of the player sprite
    playerSprite.setOrigin({TILE_SIZE / 2.0f, TILE_SIZE / 2.0f}); // Set the origin of the player sprite to the center
    playerSprite.setPosition(position); // Set the initial position of the player sprite
    playerSprite.setTexture(currentTexture); // Set the texture of the player sprite

    playerHitbox.setSize({HITBOX_SIZE,HITBOX_SIZE}); // Set the size of the player hitbox
    playerHitbox.setOrigin({HITBOX_SIZE / 2.0f, HITBOX_SIZE / 2.0f}); // Set the origin of the player hitbox to the center
    playerHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the initial position of the player hitbox
}

void Player::update(DIRECTIONS direction)
{
    switch (direction)
    {
        case UP:
            direction = UP; // Set the direction to UP
            position.y -= speed; // Move the sprite up
            if(spriteNum == 1)
                currentTexture = &up1; // Set the texture to up1
            else
                currentTexture = &up2; // Set the texture to up2
            break;
        case DOWN:
            direction = DOWN; // Set the direction to DOWN
            position.y += speed; // Move the sprite down
            if(spriteNum == 1)
                currentTexture = &down1; // Set the texture to down1
            else
                currentTexture = &down2; // Set the texture to down2
            break;
        case LEFT:
            direction = LEFT; // Set the direction to LEFT
            position.x -= speed; // Move the sprite left
            if(spriteNum == 1)
                currentTexture = &left1; // Set the texture to left1
            else
                currentTexture = &left2; // Set the texture to left2
            break;
        case RIGHT:
            direction = RIGHT; // Set the direction to RIGHT
            position.x += speed; // Move the sprite right
            if(spriteNum == 1)
                currentTexture = &right1; // Set the texture to right1
            else
                currentTexture = &right2; // Set the texture to right2
            break;
    }

    // change the sprite texture for animation every 12 frames
    spriteCount++; 
    if (spriteCount > 12)
    {
        spriteCount = 0; // Reset the sprite count
        spriteNum = (spriteNum == 1) ? 2 : 1; // Toggle between spriteNum 1 and 2 for animation
    }

    // Update the player sprite position
    playerSprite.setPosition(position); // Set the position of the player sprite
    playerHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the position of the player hitbox
    playerSprite.setTexture(currentTexture); // Set the texture of the player sprite
}