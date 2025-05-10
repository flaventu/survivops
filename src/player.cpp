#include "../include/player.hpp"
using namespace sf;


void Player::loadTextures() 
{
    // Load the textures for the player sprite
    if (!up1.loadFromFile("../../assets/entity/player/up1.png")) throw Exception("Failed to load up1 texture");
    if (!up2.loadFromFile("../../assets/entity/player/up2.png")) throw Exception("Failed to load up2 texture");
    if (!down1.loadFromFile("../../assets/entity/player/down1.png")) throw Exception("Failed to load down1 texture");
    if (!down2.loadFromFile("../../assets/entity/player/down2.png")) throw Exception("Failed to load down2 texture");
    if (!left1.loadFromFile("../../assets/entity/player/left1.png")) throw Exception("Failed to load left1 texture");
    if (!left2.loadFromFile("../../assets/entity/player/left2.png")) throw Exception("Failed to load left2 texture");
    if (!right1.loadFromFile("../../assets/entity/player/right1.png")) throw Exception("Failed to load right1 texture");
    if (!right2.loadFromFile("../../assets/entity/player/right2.png")) throw Exception("Failed to load right2 texture");
}


Player::Player()
{
    // Load the textures for the player sprite
    try {
        loadTextures(); 
    } catch (const Exception& e) {
        throw e; // Throw the exception if there is an error loading textures
    }

    position = {0, 0}; // Initialize the position of the player sprite
    speed = 4; // Set the speed of the player sprite
    totalhealth = 100.0f;
    currenthealth = totalhealth;

    entitySprite.setSize({TILE_SIZE, TILE_SIZE}); // Set the size of the player sprite
    entitySprite.setOrigin({TILE_SIZE / 2.0f, TILE_SIZE / 2.0f}); // Set the origin of the player sprite to the center
    entitySprite.setPosition(position); // Set the initial position of the player sprite
    entitySprite.setTexture(currentTexture); // Set the texture of the player sprite

    entityHitbox.setSize({HITBOX_SIZE,HITBOX_SIZE}); // Set the size of the player hitbox
    entityHitbox.setOrigin({HITBOX_SIZE / 2.0f, HITBOX_SIZE / 2.0f}); // Set the origin of the player hitbox to the center
    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the initial position of the player hitbox
}