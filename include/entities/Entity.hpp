#pragma once
#include "../const.hpp"

// Class to handle the entities
class Entity
{
    protected:

        const sf::Texture textureSheet;
        sf::Sprite entitySprite;

        // Frame dimensions
        const int frameWidth;
        const int frameHeight;
        
        // Movement variables
        DIRECTIONS direction = DOWN;
        sf::Vector2f position;
        float speed;
        int spriteNum = 0;

        // Sprite variables
        sf::FloatRect entityHitbox;

        // Health
        float totalHealth;
        float currentHealth;
        sf::Clock damageCooldown;
        sf::Clock healingClock;

        // Poison
        sf::Clock poisonClock;
        bool poisoned = false;
        float poisonDamage;


        void updateTextureRect(); // Update the texture rectangle for the sprite
        
        sf::Clock animationClock;
        virtual void animate();
        
        void checkPoison();

        // Visibility
        bool visible = true;
        void updateVisibility(const sf::View&);

    public:

        Entity(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight);

        virtual ~Entity() = default;

        // Getters
        const sf::Vector2f& get_position() const { return position; };
        const sf::FloatRect& getHitbox() const { return entityHitbox; }
        bool isVisible() const { return visible; }
        float getHealth() const { return currentHealth; }
        sf::Vector2f getPosition() const { return position; };
        DIRECTIONS getDirection() const { return direction; }
        float getHealthPerc() const { return currentHealth / totalHealth; };
        bool isPoisoned() const { return poisoned; };
        void getPoisoned(const float);

        // Setters
        void setPosition(const sf::Vector2f& newPos) { position = newPos; }
        void heal(const float heal) { currentHealth += heal; if(currentHealth > totalHealth) currentHealth = totalHealth; };
        void healing();
        void restartHealing() { healingClock.restart(); };
        void takeDamage(const float); 

        void checkStatus() { 
            checkPoison();
            if(damageCooldown.getElapsedTime().asSeconds() >= 0.5f && !poisoned) entitySprite.setColor(sf::Color::White); 
            healing();
        }

        void stopAllClocks()
        {
            damageCooldown.stop();
            poisonClock.stop();
            healingClock.stop();
        }

        void restartAllClocks()
        {
            damageCooldown.start();
            poisonClock.start();
            healingClock.start();
        }

        virtual void draw(sf::RenderWindow& window) const { window.draw(entitySprite);}
};
