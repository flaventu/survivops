#pragma once
#include "State/IState.hpp"
#include "State/StartState.hpp"
#include "Player.hpp"
#include "Tilemap.hpp"
#include "UI.hpp"


// Class to handle the game state
class GameState
{

    public:

        std::unique_ptr<IState> state; // Pointer to the current state of the game
        sf::View view; // View for the game
        Player player; // Player object
        TileMap tilemap; // Tilemap object
        UI ui;

        GameState(StartState& state);  // Constructor

        bool move_directions[4] = {false,false,false,false}; // Array to store movement directions

        sf::View get_view() const { return view; } // Get the view
        void set_view(sf::View& v) { view = v; } // Set the view

        IState& getState() const { return *state; } // Get the current state

        void changeState(std::unique_ptr<IState> newState) {
            state = std::move(newState);
        }

        void draw(sf::RenderWindow& window) const { state->draw(window); }
        void update() { state->update(); }
};

