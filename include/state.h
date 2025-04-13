#pragma once

#include <string>
#include <optional>

const std::string TITLE_IMAGE = "assets/icon.png"; // Path to the title image TO CHANGE

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
    CURRENT_STATE current_state; // Current state of the game
    sf::View view; // View for the game
public: 
    GameState(sf::RenderWindow&);  // Constructor

    CURRENT_STATE get_state() const { return current_state; } // Get the current state
    void set_state(CURRENT_STATE state) { current_state = state; } // Set the current state

    sf::View get_view() const { return view; } // Get the view
    void set_view(sf::View& v) { view = v; } // Set the view

    void draw(sf::RenderWindow&) const; // Draw the current state
    void update(float); // Update the current state
};

