#pragma once
#include "states/IState.hpp"
#include "UI.hpp"
#include "entities/Merchant.hpp"
#include "entities/Blacksmith.hpp"


// Class to handle the game state
class GameState
{

    public:

        std::unique_ptr<IState> state; // Pointer to the current state of the game (using smart pointers for automatic memory management)
        sf::View view;
        Player player;
        TileMap tilemap;
        UI ui;
        Collision collision;
        std::vector<std::shared_ptr<Entity>> npcs = {};
        std::vector<Entity*> drawable_entities = {}; // Vector to hold pointers to drawable entities

        GameState(std::unique_ptr<IState> init)
            : state(std::move(init)), player(), tilemap("assets/maps/arena.png", "assets/maps/arena.csv", 2, true), 
              view({0,0},{SCREEN_WIDTH, SCREEN_HEIGHT}), ui(), collision(tilemap)
                { 
                    npcs.push_back(std::make_shared<Merchant>("assets/entities/npcs/merchant.png", TILE_SIZE, TILE_SIZE, player));
                    npcs.push_back(std::make_shared<Blacksmith>("assets/entities/npcs/blacksmith.png", TILE_SIZE, TILE_SIZE, player));

                    if(!tilemap.isFightable())
                        tilemap.loadNpcs(npcs);
                    tilemap.update(view);
                } 

        // Load drawable entities based on visibility
        void loadDrawableEntities() {
            drawable_entities.clear();
            drawable_entities.push_back(&player);
            for (const auto& entity : tilemap.entities) {
                if(entity->isVisible()) {
                    drawable_entities.push_back(entity.get());
                }
            }
        }

        bool move_directions[4] = {false,false,false,false}; // Array to store movement directions

        void draw(sf::RenderWindow& window) const { state->draw(window); }
        void update() { state->update(); }
};

