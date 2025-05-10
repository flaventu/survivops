#include "../include/ui.hpp"
using namespace sf;
using namespace std;

UI::UI()
{
    healthBarBack.setSize(healthBarSize);
    healthBarBack.setOrigin({healthBarSize.x/2.f,healthBarSize.y/2.f});
    healthBarBack.setFillColor(Color::Red);
    healthBarBack.setOutlineColor(Color::Black);
    healthBarBack.setOutlineThickness(2);

    healthBar.setSize(healthBarSize);
    healthBar.setOrigin({healthBarSize.x/2.f,healthBarSize.y/2.f});
    healthBar.setFillColor(Color::Green);

    InventoryBack.setSize({TILE_SIZE*4, TILE_SIZE});
    InventoryBack.setOrigin({TILE_SIZE*2, TILE_SIZE/2});
    InventoryBack.setFillColor(Color(128, 128, 128));
    InventoryBack.setOutlineColor(Color::Black);
    InventoryBack.setOutlineThickness(2);
}

void UI::update(const float healthPerc, const View v, const set<Object*>& invent)
{
    healthBar.setSize({healthBarSize.x*healthPerc,healthBarSize.y});
    Vector2f viewCenter = v.getCenter();
    Vector2f viewSize = v.getSize();
    float y = viewCenter.y + (viewSize.y / 2.f) - 40.f;
    healthBarBack.setPosition({viewCenter.x, y});
    healthBar.setPosition({viewCenter.x, y});
    Vector2f InventoryPos = {viewCenter.x, y-TILE_SIZE-10.f};
    InventoryBack.setPosition(InventoryPos);
    int count = 2;
    for(const auto& obj : invent) {
        Inventory[count] = new RectangleShape(obj->getShape());
        Inventory[count]->setOrigin({TILE_SIZE/2.f, TILE_SIZE/2.f});
        Inventory[count]->setPosition({InventoryPos.x - TILE_SIZE*count + (TILE_SIZE/2), InventoryPos.y});
        
        Inventory[count]->setOutlineColor(Color::Black);
        Inventory[count]->setOutlineThickness(1);
        
        count--;
    }
}

void UI::draw(RenderWindow& window) const {
        window.draw(healthBarBack);
        window.draw(healthBar);
        window.draw(InventoryBack);
        for(const auto& obj : Inventory)
        if(obj)
            window.draw(*obj);
    }