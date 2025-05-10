#include "../include/ui.hpp"
using namespace sf;
using namespace std;

UI::UI() : font("../../assets/fonts/arial.ttf"), moneyTab(font), levelTab(font)
{

    moneyTab.setCharacterSize(25);
    moneyTab.setFillColor(Color::Yellow);
    moneyTab.setOutlineColor(Color::Black);
    moneyTab.setOutlineThickness(2);

    levelTab.setCharacterSize(30);
    levelTab.setFillColor(Color::Blue);
    levelTab.setOutlineColor(Color::Black);
    levelTab.setOutlineThickness(2);

    healthBarBack.setSize(healthBarSize);
    healthBarBack.setOrigin({healthBarSize.x/2.f,healthBarSize.y/2.f});
    healthBarBack.setFillColor(Color::Red);
    healthBarBack.setOutlineColor(Color::Black);
    healthBarBack.setOutlineThickness(2);

    healthBar.setSize(healthBarSize);
    healthBar.setOrigin({healthBarSize.x/2.f,healthBarSize.y/2.f});
    healthBar.setFillColor(Color::Green);
    
    levelBarBack.setSize(healthBarSize);
    levelBarBack.setFillColor(Color::Black);
    levelBarBack.setOutlineColor(Color::Black);
    levelBarBack.setOutlineThickness(2);

    levelBar.setSize(healthBarSize);
    levelBar.setFillColor(Color::Blue);

    InventoryBack.setSize({TILE_SIZE*4, TILE_SIZE});
    InventoryBack.setOrigin({TILE_SIZE*2, TILE_SIZE/2});
    InventoryBack.setFillColor(Color(128, 128, 128));
    InventoryBack.setOutlineColor(Color::Black);
    InventoryBack.setOutlineThickness(2);
}

void UI::update(const float healthPerc, const int money, const float expPerc, const int level, const View v, const set<Object*>& invent)
{
    healthBar.setSize({healthBarSize.x*healthPerc,healthBarSize.y});
    levelBar.setSize({healthBarSize.x*expPerc, healthBarSize.y});
    Vector2f viewCenter = v.getCenter();
    Vector2f viewSize = v.getSize();
    moneyTab.setString("Coins x" + to_string(money));
    moneyTab.setPosition({viewCenter.x-viewSize.x / 2.f + 15.f,viewCenter.y-viewSize.y  / 2.f +10.f});

    levelTab.setString(to_string(level));
    levelTab.setPosition({viewCenter.x+viewSize.x / 2.f - 30.f,viewCenter.y-viewSize.y  / 2.f +10.f});
    float y = viewCenter.y + (viewSize.y / 2.f) - 40.f;
    healthBarBack.setPosition({viewCenter.x, y});
    healthBar.setPosition({viewCenter.x, y});
    levelBarBack.setPosition({viewCenter.x + viewSize.x /2.f - healthBarSize.x - 40.f , viewCenter.y - viewSize.y / 2.f + 20.f});
    levelBar.setPosition({viewCenter.x + viewSize.x /2.f - healthBarSize.x - 40.f, viewCenter.y - viewSize.y / 2.f + 20.f});
    Vector2f InventoryPos = {viewCenter.x, y-TILE_SIZE-10.f};
    InventoryBack.setPosition(InventoryPos);

    int count = 2;
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
        window.draw(moneyTab);
        window.draw(levelTab);
        window.draw(levelBarBack);
        window.draw(levelBar);
        window.draw(healthBarBack);
        window.draw(healthBar);
        window.draw(InventoryBack);
        for(const auto& obj : Inventory)
            window.draw(obj);
    }