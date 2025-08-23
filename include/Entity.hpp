#pragma once
#include "Tilemap.hpp"

// Class to handle the entities
class Entity
{
    private:

        // Frame dimensions
        int frameWidth;
        int frameHeight;

    protected:

        // Animation clock
        sf::Clock animationClock;

        // Sprite variables
        sf::Texture textureSheet;
        sf::Sprite entitySprite;
        sf::RectangleShape entityHitbox;

        // Movement variables
        DIRECTIONS direction = DOWN;
        sf::Vector2f position;
        float speed;
        int spriteNum = 0;

        void updateTextureRect(); // Update the texture rectangle for the sprite

    public:

        Entity(const std::string& textureFile, int frameWidth, int frameHeight) 
            : textureSheet(textureFile), entitySprite(textureSheet), animationClock(), frameWidth(frameWidth), frameHeight(frameHeight) 
                { updateTextureRect(); }

        // Getters
        sf::Vector2f get_position() const { return position; };
        
        void update(const DIRECTIONS, TileMap&);
        void draw(sf::RenderWindow& window) const { window.draw(entitySprite);}
};
