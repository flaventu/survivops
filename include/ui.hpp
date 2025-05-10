#pragma once
#include "player.hpp"
#include "object.hpp"
#include <set>

const sf::Vector2f healthBarSize = {200,20};

class UI
{
    private:
        sf::RectangleShape healthBar;
        sf::RectangleShape healthBarBack;
        sf::RectangleShape *Inventory[4];
        sf::RectangleShape InventoryBack;
    public:

    UI();
    void update(const float, const sf::View, const std::set<Object*>&);
    void draw(sf::RenderWindow&) const;
};
