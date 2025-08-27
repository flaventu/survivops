#pragma once
#include <SFML/Graphics.hpp>
#include "../const.hpp"

// Class to handle the entities
class Entity
{
    private:

        // Frame dimensions
        const int frameWidth;
        const int frameHeight;

        const sf::Texture textureSheet;

        
    protected:
        
        // Sprite variables
        sf::Sprite entitySprite;
        sf::RectangleShape entityHitbox;
        
        // Movement variables
        DIRECTIONS direction = DOWN;
        sf::Vector2f position;
        float speed;
        int spriteNum = 0;
        
        void updateTextureRect(); // Update the texture rectangle for the sprite
        
        virtual void animate() = 0;
        
        bool visible = true;

        void updateVisibility(const sf::View&);

    public:

        Entity(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight);

        // Getters
        const sf::Vector2f& get_position() const { return position; };
        sf::FloatRect getHitbox() const { return entityHitbox.getGlobalBounds(); }
        const bool isVisible() const { return visible; }

        virtual void draw(sf::RenderWindow& window) const { window.draw(entitySprite);}
};
