#pragma once
#include "../Collision.hpp"

// Class to handle the entities
class Entity
{
    private:

        // Frame dimensions
        const int frameWidth;
        const int frameHeight;

        const sf::Texture textureSheet;
        
    protected:

        sf::Clock animationClock;

        // Sprite variables
        sf::Sprite entitySprite;
        sf::RectangleShape entityHitbox;

        // Movement variables
        DIRECTIONS direction = DOWN;
        sf::Vector2f position;
        float speed;
        int spriteNum = 0;

        void updateTextureRect(); // Update the texture rectangle for the sprite

    public:

        Entity(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight) 
            : textureSheet(textureFile), entitySprite(textureSheet), animationClock(), frameWidth(frameWidth), frameHeight(frameHeight) 
                { updateTextureRect(); }

        // Getters
        const sf::Vector2f& get_position() const { return position; };

        void update(const DIRECTIONS, const Collision&);
        void draw(sf::RenderWindow& window) const { window.draw(entitySprite);}
};
