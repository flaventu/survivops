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
}

void UI::update(const Player& player, const View& v)
{

    // Get the view center and size
    Vector2f viewCenter = v.getCenter();
    Vector2f viewSize = v.getSize();

    float marginBottomY = viewCenter.y + (viewSize.y / 2.f);
    float marginTopY = viewCenter.y - (viewSize.y / 2.f);

    // Update the health bar and level bar sizes based on the percentage
    healthBar.setSize({healthBarSize.x * player.getHealthPerc(), healthBarSize.y});
    levelBar.setSize({levelhBarSize.x * player.getExpPerc(), levelhBarSize.y});

    // Update the money tab
    moneyTab.setString("Coins x" + to_string(player.getMoney()));
    moneyTab.setPosition({viewCenter.x - viewSize.x / 2.f + 15.f, marginTopY + 10.f}); // Top left corner

    // Update the level tab
    levelTab.setString("Level " + to_string(player.getCurrentLevel()));
    Vector2f levelTabSize = {levelTab.getLocalBounds().size.x,levelTab.getLocalBounds().size.y};
    levelTab.setOrigin({levelTabSize.x / 2.f, levelTabSize.y / 2.f});
    levelTab.setPosition({viewCenter.x, marginTopY + levelTabSize.y}); // Top center

    // Update the health bar position (bottom centered)
    healthBarBack.setPosition({viewCenter.x, marginBottomY - 40.f});
    healthBar.setPosition({viewCenter.x, marginBottomY - 40.f});

    // Update the level bar position (top centered)
    levelBarBack.setPosition({viewCenter.x, marginTopY + levelhBarSize.y + levelTabSize.y + 20.f});
    levelBar.setPosition({viewCenter.x, marginTopY + levelhBarSize.y + levelTabSize.y + 20.f});

}

void UI::draw(RenderWindow& window) const {
        window.draw(moneyTab); // money count
        window.draw(levelTab); // level count
        window.draw(levelBarBack); // level bar back
        window.draw(levelBar); // level bar
        window.draw(healthBarBack); // health bar back
        window.draw(healthBar); // health bar
    }