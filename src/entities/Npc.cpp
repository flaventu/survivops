#include "../include/entities/Npc.hpp"
using namespace std;
using namespace sf;

void Npc::spawn(const TileMap& tilemap) {

    while(true) {
        int x = rand() % tilemap.getWidth();
        int y = rand() % tilemap.getHeight();

        if(!tilemap.isSolid({x, y})) {
            position = Vector2f{ x * TILE_SIZE - tilemap.getMapSize().x / 2.f + TILE_SIZE / 2.f,
                         y * TILE_SIZE - tilemap.getMapSize().y / 2.f + TILE_SIZE / 2.f };
            break;
        }
    }
}

void Npc::move(const Collision& collision) {
    int timeElapsed = moveClock.getElapsedTime().asMilliseconds();
    if(timeElapsed > 600 && timeElapsed % 200 < 15) {
        update(direction, collision);
        if(timeElapsed > 1200)
        {
            direction = static_cast<DIRECTIONS>(rand() % 4);
            moveClock.restart();
        }
    }
}
