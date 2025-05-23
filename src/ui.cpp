#include "../include/ui.hpp"
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

    // Prepare the inventory background
    InventoryBack.setSize({TILE_SIZE*4, TILE_SIZE}); // 4 slots
    InventoryBack.setOrigin({TILE_SIZE*2, TILE_SIZE/2});
    InventoryBack.setFillColor(Color(128, 128, 128)); // Grey color
    InventoryBack.setOutlineColor(Color::Black);
    InventoryBack.setOutlineThickness(2);
}

void UI::update(const float healthPerc, const int money, const float expPerc, const int level, const View v, const set<Object*>& invent)
{

    // Get the view center and size
    Vector2f viewCenter = v.getCenter();
    Vector2f viewSize = v.getSize();

    float marginBottomY = viewCenter.y + (viewSize.y / 2.f);
    float marginTopY = viewCenter.y - (viewSize.y / 2.f);

    // Update the health bar and level bar sizes based on the percentage
    healthBar.setSize({healthBarSize.x * healthPerc, healthBarSize.y});
    levelBar.setSize({levelhBarSize.x * expPerc, levelhBarSize.y});

    // Update the money tab
    moneyTab.setString("Coins x" + to_string(money));
    moneyTab.setPosition({viewCenter.x - viewSize.x / 2.f + 15.f, marginTopY + 10.f}); // Top left corner

    // Update the level tab
    levelTab.setString("Level " + to_string(level));
    Vector2f levelTabSize = {levelTab.getLocalBounds().size.x,levelTab.getLocalBounds().size.y};
    levelTab.setOrigin({levelTabSize.x / 2.f, levelTabSize.y / 2.f});
    levelTab.setPosition({viewCenter.x, marginTopY + levelTabSize.y}); // Top center

    // Update the health bar position (bottom centered)
    healthBarBack.setPosition({viewCenter.x, marginBottomY - 40.f});
    healthBar.setPosition({viewCenter.x, marginBottomY - 40.f});

    // Update the level bar position (top centered)
    levelBarBack.setPosition({viewCenter.x, marginTopY + levelhBarSize.y + levelTabSize.y + 20.f});
    levelBar.setPosition({viewCenter.x, marginTopY + levelhBarSize.y + levelTabSize.y + 20.f});


    Vector2f InventoryPos = {viewCenter.x, marginBottomY - 40.f - TILE_SIZE-10.f};
    InventoryBack.setPosition(InventoryPos);

    int count = 2; // 2 tiles to the left of the center
    for(const auto& obj : invent) {
        Inventory[count] = (obj->getShape());
        Inventory[count].setOrigin({TILE_SIZE/2.f, TILE_SIZE/2.f});
        Inventory[count].setPosition({InventoryPos.x - TILE_SIZE*count + (TILE_SIZE/2), InventoryPos.y});
        
        Inventory[count].setOutlineColor(Color::Black);
        Inventory[count].setOutlineThickness(1);
        
        count--;
    }

}

void UI::draw(RenderWindow& window) const {
        window.draw(moneyTab); // money count
        window.draw(levelTab); // level count
        window.draw(levelBarBack); // level bar back
        window.draw(levelBar); // level bar
        window.draw(healthBarBack); // health bar back
        window.draw(healthBar); // health bar
        window.draw(InventoryBack); // inventory background
        for(const auto& obj : Inventory)
            window.draw(obj); // inventory items
    }