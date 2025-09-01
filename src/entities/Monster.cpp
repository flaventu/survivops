#include "../../include/entities/Monster.hpp"
#include "../../include/Tilemap.hpp"
#include "../../include/entities/Player.hpp"
#include "../../include/Collision.hpp"
using namespace sf;

void Monster::update(const sf::Vector2i& playerPosition, const sf::View& view, const TileMap& tilemap, const Collision& collision, Player& player) {

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
        // followPlayer(playerPosition);
        if(!collision.collision(getHitbox(), direction, speed))
        {
            if(!isVisible() || !collision.collision(getHitbox(), direction, speed, player.getHitbox()))
            {
                position = newPosition; // Update the position if there is no collision
                animate();
            }
            else {
                attack(player);
            }
        }

        entitySprite.setPosition(position);
        entityHitbox.position = {position.x - (HITBOX_SIZE / 2), position.y - (HITBOX_SIZE / 2) + HITBOX_OFFSET};
        updateTextureRect();

        checkDamage();

        // Change direction randomly after a certain period
        if(timeElapsed > 1200)
        {
            direction = static_cast<DIRECTIONS>(rand() % 4);
            moveClock.restart();
        }
    }

    updateVisibility(view);
}

void Monster::attack(Player& target) {

    target.takeDamage(power);

}