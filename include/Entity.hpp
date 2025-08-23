#pragma once
#include "Tilemap.hpp"

// Class to handle the entities
class Entity
{
    protected:

        // Health variables
        float totalhealth;
        float currenthealth;

        // Sprite variables
        sf::Texture textureSheet;
        sf::Sprite entitySprite;
        sf::RectangleShape entityHitbox;
        int frameWidth;
        int frameHeight;

        // Movement variables
        DIRECTIONS direction = DOWN;
        sf::Vector2f position;
        float speed;
        int spriteNum = 0;

        void updateTextureRect(); // Update the texture rectangle for the sprite

    public:

        Entity(const std::string& textureFile, int frameWidth, int frameHeight) 
            : textureSheet(textureFile), entitySprite(textureSheet), frameWidth(frameWidth), frameHeight(frameHeight) { updateTextureRect(); }

        // Getters
        sf::Vector2f get_position() const { return position; };
        float getHealth() const { return currenthealth; };
        float getHealthPerc() const { return currenthealth/totalhealth; };
        
        void update(const DIRECTIONS, TileMap&, sf::Clock&);
        void draw(sf::RenderWindow& window) const { window.draw(entitySprite);}
};
