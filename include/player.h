#pragma once
#include "const.h"

enum DIRECTIONS
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Player
{
private:
    sf::RectangleShape sprite; // Sprite for the player
    float speed = 4; // Speed of the player
public:
    Player();
    void move(DIRECTIONS); // Move the player in a direction with a speed
    sf::Vector2f get_position() const; // Get the position of the player

    void draw(sf::RenderWindow& window) const { window.draw(sprite); } // Draw the player sprite on the window
};
