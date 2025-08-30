#include "../include/UI.hpp"
using namespace sf;
using namespace std;

UI::UI() : font("assets/fonts/arial.ttf"), moneyTab(font), levelTab(font), weaponLevel(font)
{
    
    // Prepare the money text
    moneyTab.setCharacterSize(FONTSIZE);
    moneyTab.setFillColor(Color::Yellow);
    moneyTab.setOutlineColor(Color::Black);
    moneyTab.setOutlineThickness(2);

    // Prepare the level text
    levelTab.setCharacterSize(FONTSIZE-2);
    levelTab.setFillColor(Color::Blue);
    levelTab.setOutlineColor(Color::Black);
    levelTab.setOutlineThickness(1);

    // Prepare the weapon level text
    weaponLevel.setCharacterSize(FONTSIZE-8);
    weaponLevel.setOutlineColor(Color::Black);
    weaponLevel.setOutlineThickness(1);

    // Prepare the health bar back
    healthBarBack.setSize(healthBarSize);
    healthBarBack.setOrigin({healthBarSize.x/2.f,healthBarSize.y/2.f});
    healthBarBack.setFillColor(Color::Red);
    healthBarBack.setOutlineColor(Color::Black);
    healthBarBack.setOutlineThickness(2);

    // Prepare the health bar
    healthBar.setSize(healthBarSize);
    healthBar.setOrigin({healthBarSize.x/2.f,healthBarSize.y/2.f});
    healthBar.setFillColor(Color::Green);
    
    // Prepare the level bar back
    levelBarBack.setSize(levelhBarSize);
    levelBarBack.setOrigin({levelhBarSize.x/2.f,levelhBarSize.y/2.f});
    levelBarBack.setFillColor(Color::Black);
    levelBarBack.setOutlineColor(Color::White);
    levelBarBack.setOutlineThickness(1);

    // Prepare the level bar
    levelBar.setSize(levelhBarSize);
    levelBar.setOrigin({levelhBarSize.x/2.f,levelhBarSize.y/2.f});
    levelBar.setFillColor(Color::Blue);

    // Prepare the weapon background
    weaponBack.setSize({TILE_SIZE, TILE_SIZE + TILE_SIZE/4.f});
    weaponBack.setOrigin({TILE_SIZE / 2.f, TILE_SIZE / 2.f});
    weaponBack.setFillColor(Color(0, 0, 0, 100));
    weaponBack.setOutlineColor(Color::Black);
    weaponBack.setOutlineThickness(2);

    // Prepare the position of the UI elements
    moneyTab.setPosition({15.f, 10.f});
    levelTab.setPosition({SCREEN_WIDTH / 2.f, 20.f});
    levelBarBack.setPosition({SCREEN_WIDTH / 2.f, 45.f});
    levelBar.setPosition(levelBarBack.getPosition());
    healthBarBack.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 35.f});
    healthBar.setPosition(healthBarBack.getPosition());
    weaponBack.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 96.f});
    weaponLevel.setPosition(weaponBack.getPosition());
}

void UI::update(const Player& player)
{

    // Update the health bar and level bar sizes based on the percentage
    healthBar.setSize({healthBarSize.x * player.getHealthPerc(), healthBarSize.y});
    levelBar.setSize({levelhBarSize.x * player.getExpPerc(), levelhBarSize.y});

    // Update the money tab
    moneyTab.setString("Coins x" + to_string(player.getMoney()));

    // Update the level tab
    levelTab.setString("Level " + to_string(player.getCurrentLevel()));

    weaponLevel.setString("Lv. " + to_string(player.getWeapon().getLevel()));

    setWeaponLevelColor(player.getWeapon().getLevel());

    Vector2f levelTabSize = {levelTab.getLocalBounds().size.x,levelTab.getLocalBounds().size.y};
    levelTab.setOrigin({levelTabSize.x / 2.f, levelTabSize.y / 2.f});

    weaponLevel.setOrigin({weaponLevel.getLocalBounds().size.x / 2.f, weaponLevel.getLocalBounds().size.y / 2.f});
    weaponLevel.setPosition({weaponBack.getPosition().x, weaponBack.getPosition().y - weaponBack.getSize().y / 4.f});
}

void UI::draw(RenderWindow& window) const {

    window.draw(moneyTab);
    window.draw(levelTab);
    window.draw(levelBarBack);
    window.draw(levelBar);
    window.draw(healthBarBack); 
    window.draw(healthBar);
    window.draw(weaponBack);
    window.draw(weaponLevel);
}

void UI::setWeaponLevelColor(const int level) {
    
    switch (level)
    {
    case 2: // Gold
        weaponLevel.setFillColor(Color(255, 215, 0));
        break;

    case 3: // Amethyst
        weaponLevel.setFillColor(Color(153, 102, 204));
        break;

    case 4: // Diamond
        weaponLevel.setFillColor(Color(78, 226, 236));
        break;

    case 5: // Obsidian
        weaponLevel.setFillColor(Color(49, 41, 42));
        break;

    default: // Bronze
        weaponLevel.setFillColor(Color(205, 127, 50));
        break;
    }
}