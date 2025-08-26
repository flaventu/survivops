#include "../include/entities/Npc.hpp"
using namespace std;
using namespace sf;

void Npc::spawn(const TileMap& tilemap) {

    while(true) {
        int x = rand() % tilemap.getWidth();
        int y = rand() % tilemap.getHeight();

        if(!tilemap.isSolid({x, y})) {
            position = Vector2f{ x * TILE_SIZE - tilemap.getMapSize().x / 2.f + TILE_SIZE / 2.f,
                         y * TILE_SIZE - tilemap.getMapSize().y / 2.f + TILE_SIZE / 2.f };
            break;
        }
    }
}

void Npc::update(const Collision& collision, const sf::View& view, const FloatRect& playerHitbox)
{

    int timeElapsed = moveClock.getElapsedTime().asMilliseconds();

    if(timeElapsed > 600 && timeElapsed % 200 < 15) {

        Vector2f newPosition = position;

        switch (direction)
        {
            case UP: newPosition.y -= speed; break;
            case DOWN: newPosition.y += speed; break;
            case LEFT: newPosition.x -= speed; break;
            case RIGHT: newPosition.x += speed; break;
            default: break;
        }

        if(!collision.collision(entityHitbox.getGlobalBounds(), direction, speed) && !collision.collision(entityHitbox.getGlobalBounds(), direction, speed, playerHitbox))
        {
            position = newPosition; // Update the position if there is no collision

            animate();
        }

        // Update the entity sprite position
        entitySprite.setPosition(position);
        entityHitbox.setPosition({position.x, position.y + HITBOX_OFFSET}); // Set the position of the entity hitbox
        updateTextureRect();

        if(timeElapsed > 1200)
        {
            direction = static_cast<DIRECTIONS>(rand() % 4);
            moveClock.restart();
        }
    }

    updateVisibility(view);
}