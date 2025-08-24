#pragma once
#include "Player.hpp"

inline const sf::Vector2f levelhBarSize = {180,10};
inline const sf::Vector2f healthBarSize = {200,20};
inline constexpr int FONTSIZE = 25;

class UI
{
    private:
        sf::Font font;
        sf::Text moneyTab;
        sf::Text levelTab;

        sf::RectangleShape levelBar;
        sf::RectangleShape levelBarBack;

        sf::RectangleShape healthBar;
        sf::RectangleShape healthBarBack;
    public:

    UI();
    void update(const Player&, const sf::View&);
    void draw(sf::RenderWindow&) const;
};
