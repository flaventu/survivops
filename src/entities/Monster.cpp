#include "../../include/entities/Monster.hpp"
#include "../../include/Tilemap.hpp"
#include "../../include/entities/Player.hpp"
#include "../../include/Collision.hpp"
using namespace sf;

Monster::Monster(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const int level)
    : Entity(textureFile, frameWidth, frameHeight), moveClock(), animationClock(), pathClock(), levelFont("assets/fonts/arial.ttf"), levelText(levelFont), level(level)
{
    levelText.setCharacterSize(15);
    levelText.setFillColor(Color::White);
    levelText.setOutlineColor(Color::Black);
    levelText.setOutlineThickness(1);
    levelText.setString("Lv." + std::to_string(level));

    // Position of level text
    Vector2f levelTextSize = {levelText.getLocalBounds().size.x,levelText.getLocalBounds().size.y};
    levelText.setOrigin({levelTextSize.x / 2.f, levelTextSize.y / 2.f});

    // Prepare the health bar back
    healthBarBack.setSize({TILE_SIZE, 5.f});
    healthBarBack.setOrigin({healthBarBack.getSize().x / 2.f, healthBarBack.getSize().y / 2.f});
    healthBarBack.setFillColor(Color::Red);
    healthBarBack.setOutlineColor(Color::Black);
    healthBarBack.setOutlineThickness(2);

    // Prepare the health bar
    healthBar.setSize(healthBarBack.getSize());
    healthBar.setOrigin({healthBar.getSize().x / 2.f, healthBar.getSize().y / 2.f});
    healthBar.setFillColor(Color::Green);
}

void Monster::update(const sf::Vector2i& playerPosition, const sf::View& view, const TileMap& tilemap, const Collision& collision, Player& player) {

    int timeElapsed = pathClock.getElapsedTime().asMilliseconds();

    if((isVisible() && timeElapsed > 400) || timeElapsed > 800) {

        Vector2i monsterPosition = tilemap.positionToTile(position);

        path.clear();
        
        // Calculate the direction with A* pathfinding
        path = aStarPath(monsterPosition, playerPosition,
            [&](const sf::Vector2i& tile) {
                return !tilemap.isSolid(tile);
            },
            {tilemap.getWidth(), tilemap.getHeight()});
    
        pathClock.restart();
    }

    // Every 75 ms move the monster
    if(moveClock.getElapsedTime().asMilliseconds() > 75) {

        // If the monster has a path, follow it
        if(!path.empty()) {

            // Get the next tile and position
            sf::Vector2i nextTile = path.front();
            sf::Vector2f nextPos = tilemap.tileToPosition(nextTile);

            sf::Vector2f delta = nextPos - position;
            // If the monster has reached the next position, update the path
            if(delta.x * delta.x + delta.y * delta.y < speed * speed) {
                path.erase(path.begin());
                if(path.empty()) return;
                nextTile = path.front();
                nextPos = tilemap.tileToPosition(nextTile);
                delta = nextPos - position;
            }

            // Calculate the direction
            if(std::abs(delta.x) > std::abs(delta.y)) {
                direction = (delta.x > 0) ? RIGHT : LEFT;
            } else {
                direction = (delta.y > 0) ? DOWN : UP;
            }
        }

        Vector2f newPosition = position;

        switch (direction)
        {
            case UP: newPosition.y -= speed; break;
            case DOWN: newPosition.y += speed; break;
            case LEFT: newPosition.x -= speed; break;
            case RIGHT: newPosition.x += speed; break;
            default: break;
        }

        if(!collision.collision(getHitbox(), direction, speed))
        {
            if(!isVisible() || !collision.collision(getHitbox(), direction, speed, player.getHitbox()))
            {
                position = newPosition; // Update the position if there is no collision
                animate();
            }
            else
                // If the monster collides with the player, attack
                attack(player);
        } else {
            // If the monster is stuck, reset path and change direction randomly
            path.clear();
            direction = static_cast<DIRECTIONS>(rand() % 4);
        }

        entitySprite.setPosition(position);
        entityHitbox.position = {position.x - (HITBOX_SIZE / 2), position.y - (HITBOX_SIZE / 2) + HITBOX_OFFSET};
        updateTextureRect();
        checkDamage();
        moveClock.restart();
    }

    updateVisibility(view);
    if(isVisible()) updateUI();
    
}

void Monster::updateUI() {
    levelText.setPosition({position.x, position.y - TILE_SIZE});
    healthBarBack.setPosition({position.x, position.y - TILE_SIZE * 0.65f});
    healthBar.setPosition(healthBarBack.getPosition());
    healthBar.setSize({healthBarBack.getSize().x * getHealthPerc(), healthBarBack.getSize().y});
}

void Monster::attack(Player& target) {

    target.takeDamage(power);

}

void Monster::draw(sf::RenderWindow& window) const {

    Entity::draw(window);
    window.draw(levelText);
    window.draw(healthBarBack);
    window.draw(healthBar);
}
