#pragma once
#include "const.hpp"

enum DIRECTIONS
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

inline constexpr int SPEED = 4; // Speed of the player

// Class to handle the player character
class Player
{
    private:

        sf::Texture up1, up2, down1, down2, left1, left2, right1, right2; // Textures for the player sprite 
        sf::Texture* currentTexture; // Pointer to the current texture
        DIRECTIONS direction = DOWN; // Current direction of the player
        sf::Vector2f position = {0,0}; // Position of the player

        int spriteCount = 0; // Counter for sprite animation
        int spriteNum = 1; // Number of sprite for animation

        void loadTextures(); // Load textures for the player sprite

    public:


        Player(); // Constructor to initialize the player sprite
        void update(DIRECTIONS); // Move the player in a direction with a speed and update the sprite
        sf::Vector2f get_position() const { return position; }; // Get the position of the player

        void draw(sf::RenderWindow& window) const; // Draw the player sprite on the window
};
