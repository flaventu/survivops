#include "../../include/entities/Monster.hpp"
#include "../../include/Tilemap.hpp"
#include "../../include/entities/Player.hpp"
#include "../../include/Collision.hpp"
using namespace sf;

Monster::Monster(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight)
    : Entity(textureFile, frameWidth, frameHeight), moveClock(), animationClock(), levelFont("assets/fonts/arial.ttf"), levelText(levelFont) 
{
    levelText.setCharacterSize(15);
    levelText.setFillColor(Color::White);
    levelText.setOutlineColor(Color::Black);
    levelText.setOutlineThickness(1);
    levelText.setString("Lv." + std::to_string(level));

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

    if(isVisible()) {
        updateUI();
    }
}

void Monster::updateUI() {
    
    Vector2f levelTextSize = {levelText.getLocalBounds().size.x,levelText.getLocalBounds().size.y};
    levelText.setOrigin({levelTextSize.x / 2.f, levelTextSize.y / 2.f});
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
