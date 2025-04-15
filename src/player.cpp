#include "../include/player.h"
using namespace sf;

Player::Player() 
{
    sprite.setSize({TILE_SIZE, TILE_SIZE}); // Set the size of the sprite to the tile size
    sprite.setOrigin({TILE_SIZE/2, TILE_SIZE/2}); // Set the origin of the sprite to the center
    sprite.setPosition({0,0}); // Set the initial position of the sprite to (0,0)
    
    sprite.setFillColor(Color::White); // Set the fill color of the sprite to white TO CHANGE
}

void Player::move(DIRECTIONS direction)
{
    switch (direction)
    {
        case UP:
            sprite.move({0, -speed}); // Move the sprite up
            break;
        case DOWN:
            sprite.move({0, speed}); // Move the sprite down
            break;
        case LEFT:
            sprite.move({-speed, 0}); // Move the sprite left
            break;
        case RIGHT:
            sprite.move({speed, 0}); // Move the sprite right
            break;
    }
}

Vector2f Player::get_position() const
{
    return sprite.getPosition(); // Return the position of the sprite
}