#include "../include/entities/Entity.hpp"
using namespace sf;
using namespace std;

Entity::Entity(const filesystem::path& textureFile, const int frameWidth, const int frameHeight) 
    : textureSheet(textureFile), entitySprite(textureSheet), frameWidth(frameWidth), frameHeight(frameHeight), 
      entityHitbox({position.x - (HITBOX_SIZE / 2), position.y - (HITBOX_SIZE / 2) + HITBOX_OFFSET},{ HITBOX_SIZE, HITBOX_SIZE}) 
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
