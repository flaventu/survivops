#pragma once
#include "states/IState.hpp"
#include "UI.hpp"
#include "entities/Merchant.hpp"
#include "entities/Npc.hpp"


// Class to handle the game state
class GameState
{
    private:

        void loadNpcs() {

            // Merchant NPC
            npcs.push_back(std::make_unique<Merchant>("assets/entities/npcs/merchant/spritesheet.png", TILE_SIZE, TILE_SIZE, tilemap));

        }

        void loadDrawableEntities() {
            drawable_entities.push_back(&player);
            for (const auto& npc : npcs) {
                drawable_entities.push_back(npc.get());
            }
        }

    public:

        std::unique_ptr<IState> state; // Pointer to the current state of the game (using smart pointers for automatic memory management)
        sf::View view;
        Player player;
        TileMap tilemap;
        UI ui;
        Collision collision;
        std::vector<std::unique_ptr<Npc>> npcs;
        std::vector<Entity*> drawable_entities;

        GameState(std::unique_ptr<IState> init)
            : state(std::move(init)), player(), tilemap("../../assets/maps/map1.png", "../../assets/maps/map1.csv", 5), 
              view({0,0},{SCREEN_WIDTH, SCREEN_HEIGHT}), ui(), collision(tilemap)
                { 
                    tilemap.update(view);
                    loadNpcs();
                    loadDrawableEntities();
                } 

        bool move_directions[4] = {false,false,false,false}; // Array to store movement directions

        void draw(sf::RenderWindow& window) const { state->draw(window); }
        void update() { state->update(); }
};

