#pragma once
#include "const.hpp"


class Object
{
private:
    std::string name; // Name of the object
    sf::Vector2f position; // Position of the object
    sf::Texture texture; // Texture of the object
    sf::RectangleShape shape; // Shape of the object
    int tilex, tiley; // Tile coordinates of the object
    bool visible = false; // Visibility of the object
public:
    Object(const sf::Texture& text, const sf::Vector2f& pos, const sf::Vector2f& size, std::string n)
    {
        name = n; // Set the name of the object
        texture = text; // Set the texture of the object
        position = pos; // Set the position of the object
        shape.setTexture(&texture); // Set the texture of the shape
        shape.setSize(size); // Set the size of the shape
        shape.setPosition(position); // Set the position of the shape
    }
    sf::RectangleShape getShape() const { return shape; } // Get the shape of the object
    sf::Vector2f getPosition() const { return position; } // Get the position of the object
    void setTiles(const sf::Vector2f& tiles) { tilex = tiles.x; tiley = tiles.y; } // Set the tile coordinates of the object
    sf::Vector2i getTiles() const { return {tilex, tiley}; } // Get the tile coordinates of the object
    void setVisible(bool vis) { visible = vis; } // Set the visibility of the object
    bool isVisible() const { return visible; } // Get the visibility of the object
    std::string getName() const { return name; } // Get the name of the object
};
