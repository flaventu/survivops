#include "../include/entities/Entity.hpp"
using namespace sf;
using namespace std;

Entity::Entity(const filesystem::path& textureFile, const int frameWidth, const int frameHeight) 
    : textureSheet(textureFile), entitySprite(textureSheet), frameWidth(frameWidth), frameHeight(frameHeight), 
      entityHitbox({position.x - (HITBOX_SIZE / 2), position.y - (HITBOX_SIZE / 2) + HITBOX_OFFSET},{ HITBOX_SIZE, HITBOX_SIZE}), damageCooldown(), animationClock(), healingClock()
{
    
    entitySprite.setOrigin({TILE_SIZE / 2.0f, TILE_SIZE / 2.0f});
    entitySprite.setPosition(position);

    updateTextureRect(); 
}

void Entity::updateTextureRect() {

    IntRect rect;
    rect.position.x = spriteNum * frameWidth;
    rect.position.y = direction * frameHeight;
    rect.size.x = frameWidth;
    rect.size.y = frameHeight;

    entitySprite.setTextureRect(rect);
}

void Entity::updateVisibility(const sf::View& view)
{
    Vector2f topLeft = view.getCenter() - view.getSize() / 2.f - sf::Vector2f{TILE_SIZE / 2.f, TILE_SIZE / 2.f};
    Vector2f bottomRight = view.getCenter() + view.getSize() / 2.f + sf::Vector2f{TILE_SIZE / 2.f, TILE_SIZE / 2.f};

    visible = (position.x > topLeft.x && position.x < bottomRight.x &&
               position.y > topLeft.y && position.y < bottomRight.y);
}

void Entity::takeDamage(const float damage) 
{ 
    if(damageCooldown.getElapsedTime().asSeconds() < 0.5f) return; // Invulnerability period after taking damage
    currentHealth -= damage; 
    entitySprite.setColor(sf::Color::Red); 
    damageCooldown.restart();
    if(currentHealth < 0) currentHealth = 0; 
};

void Entity::getPoisoned(const int damage) {
    if(!poisoned) {
        poisoned = true;
        poisonDamage = damage;
        poisonClock.restart();
    }
}

void Entity::checkPoison() {
    if (poisoned) {

        // 5s of poison damage
        if (poisonClock.getElapsedTime().asSeconds() < 5.f) {

            entitySprite.setColor(Color::Green);

            // every ~ 1s
            if(poisonClock.getElapsedTime().asMilliseconds() % 1000 < 15)
                takeDamage(poisonDamage);

        } else 
            poisoned = false;
    }
}

void Entity::animate()
{
    // update the sprite animation every 200 milliseconds (12 frames at 60 FPS)
    if(animationClock.getElapsedTime().asMilliseconds() > 200) {
        spriteNum = (spriteNum + 1) % 2; // Toggle between spriteNum 0 and 1
        animationClock.restart();
    }
}

void Entity::healing()
{
    if(healingClock.getElapsedTime().asSeconds() >= 60.f) {
        heal(totalHealth * 0.1f); // Heal 10% HP every minute
        entitySprite.setColor(sf::Color::Green);
        healingClock.restart();
    }
}