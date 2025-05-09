#pragma once
#include "tilemap.hpp"

// Class to handle the player character
class Entity
{
    protected:

        sf::Texture up1, up2, down1, down2, left1, left2, right1, right2; // Textures for the entity sprite 
        sf::Texture* currentTexture = &down1; // Pointer to the current texture
        DIRECTIONS direction = DOWN; // Current direction of the entity
        sf::Vector2f position; // Position of the entity
        float speed; // Speed of the entity
        sf::RectangleShape entitySprite; // Rectangle shape for the entity sprite
        sf::RectangleShape entityHitbox; // Rectangle shape for the entity hitbox

        int spriteCount = 0; // Counter for sprite animation
        int spriteNum = 1; // Number of sprite for animation

        virtual void loadTextures() = 0; // Load textures for the entity sprite

    public:

        void update(const DIRECTIONS, const TileMap&); // Move the entity in a direction with a speed and update the sprite
        sf::Vector2f get_position() const { return position; }; // Get the position of the entity

        void draw(sf::RenderWindow& window) const { window.draw(entitySprite);} // Draw the entity sprite on the window
};
