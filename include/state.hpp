#pragma once
#include "player.hpp"
#include "tilemap.hpp"

// Game state enum
enum CURRENT_STATE {
    INIT,
    RUNNING,
    PAUSED,
    STOPPED,
};


// Class to handle the game state
class GameState
{
    private:

        CURRENT_STATE current_state = INIT; // Current state of the game
        sf::View view; // View for the game
        Player *player; // Player object
        TileMap *tilemap; // Tilemap object

    public:

        GameState();  // Constructor

        bool move_directions[4] = {false,false,false,false}; // Array to store movement directions

        CURRENT_STATE get_state() const { return current_state; } // Get the current state
        void set_state(CURRENT_STATE state) { current_state = state; } // Set the current state

        sf::View get_view() const { return view; } // Get the view
        void set_view(sf::View& v) { view = v; } // Set the view

        Player& get_player() const { return *player; } // Get the player object

        void draw(sf::RenderWindow&) const; // Draw the current state
        void update(); // Update the current state
};

