#include "../include/entities/Entity.hpp"
using namespace sf;

Entity::Entity(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight) 
            : textureSheet(textureFile), entitySprite(textureSheet), frameWidth(frameWidth), frameHeight(frameHeight) 
{
    
    entitySprite.setOrigin({TILE_SIZE / 2.0f, TILE_SIZE / 2.0f});
    entitySprite.setPosition(position);
    
    entityHitbox.setSize({HITBOX_SIZE,HITBOX_SIZE});
    entityHitbox.setOrigin({HITBOX_SIZE / 2.0f, HITBOX_SIZE / 2.0f});
    entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET});

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
