#pragma once
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
        sf::FloatRect entityHitbox;
        
        // Movement variables
        DIRECTIONS direction = DOWN;
        sf::Vector2f position;
        float speed;
        int spriteNum = 0;

        // Health
        float totalHealth;
        float currentHealth;
        
        void updateTextureRect(); // Update the texture rectangle for the sprite
        
        virtual void animate() = 0; // Pure virtual function for animation

        // Visibility
        bool visible = true;
        void updateVisibility(const sf::View&);

    public:

        Entity(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight);

        // Getters
        const sf::Vector2f& get_position() const { return position; };
        const sf::FloatRect& getHitbox() const { return entityHitbox; }
        const bool isVisible() const { return visible; }
        const float getHealth() const { return currentHealth; }
        sf::Vector2f getPosition() const { return position; };

        // Setters
        void setPosition(const sf::Vector2f& newPos) { position = newPos; }
        void heal(const float heal) { currentHealth += heal; if(currentHealth > totalHealth) currentHealth = totalHealth; };
        void takeDamage(const float damage) { currentHealth -= damage; if(currentHealth < 0) currentHealth = 0; };

        virtual void draw(sf::RenderWindow& window) const { window.draw(entitySprite);}
};
