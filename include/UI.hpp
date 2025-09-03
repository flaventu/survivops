#pragma once
#include "entities/Player.hpp"

inline const sf::Vector2f levelhBarSize = {180,10};
inline const sf::Vector2f healthBarSize = {200,20};
inline constexpr int FONTSIZE = 25;

class UI
{
    private:
    
        sf::Font font;
        sf::Text moneyTab;
        sf::Text levelTab;
        sf::Text weaponLevel;

        sf::RectangleShape levelBar;
        sf::RectangleShape levelBarBack;

        sf::RectangleShape healthBar;
        sf::RectangleShape healthBarBack;

        sf::RectangleShape weaponBack;

        sf::CircleShape playerAttackCircle;

        sf::Texture currentMapTexture;
        sf::Sprite currentMapSprite;

        void setWeaponLevelColor(const int level);

    public:

        UI();

        void updateMapTexture(const std::filesystem::path& path) 
        { 
            if(!currentMapTexture.loadFromFile(path)) {
                throw std::runtime_error("Failed to load UI map texture from " + path.string());
            }
            currentMapSprite.setTexture(currentMapTexture); 
        }

        void update(const Player&, const bool);
        void draw(sf::RenderWindow&) const;
};
