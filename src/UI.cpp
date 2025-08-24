#include "../include/UI.hpp"
using namespace sf;
using namespace std;

UI::UI() : font("../../assets/fonts/arial.ttf"), moneyTab(font), levelTab(font)
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

    // Prepare the position of the UI elements
    moneyTab.setPosition({15.f, 10.f});
    levelTab.setPosition({SCREEN_WIDTH / 2.f, 20.f});
    levelBarBack.setPosition({SCREEN_WIDTH / 2.f, 45.f});
    levelBar.setPosition(levelBarBack.getPosition());
    healthBarBack.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 35.f});
    healthBar.setPosition(healthBarBack.getPosition());
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
    Vector2f levelTabSize = {levelTab.getLocalBounds().size.x,levelTab.getLocalBounds().size.y};
    levelTab.setOrigin({levelTabSize.x / 2.f, levelTabSize.y / 2.f});

}

void UI::draw(RenderWindow& window) const {

    window.draw(moneyTab);
    window.draw(levelTab);
    window.draw(levelBarBack);
    window.draw(levelBar);
    window.draw(healthBarBack); 
    window.draw(healthBar);
}