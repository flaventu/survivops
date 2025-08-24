#pragma once
#include "State/IState.hpp"
#include "Player.hpp"
#include "Tilemap.hpp"
#include "UI.hpp"


// Class to handle the game state
class GameState
{

    public:

        std::unique_ptr<IState> state; // Pointer to the current state of the game (using smart pointers for automatic memory management)
        sf::View view;
        Player player;
        TileMap tilemap;
        UI ui;

        GameState(std::unique_ptr<IState> init)
            : state(std::move(init)), player(), tilemap("../../assets/maps/map1.png", "../../assets/maps/map1.csv", 5), 
              view({0,0},{SCREEN_WIDTH, SCREEN_HEIGHT}), ui()
                {}

        bool move_directions[4] = {false,false,false,false}; // Array to store movement directions

        void draw(sf::RenderWindow& window) const { state->draw(window); }
        void update() { state->update(); }
};

