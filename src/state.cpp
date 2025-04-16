#include "../include/const.hpp"
#include "../include/state.hpp"
using namespace sf;


GameState::GameState() : player(new Player()), view() // Initialize the player and view objects
{
    view.setSize({SCREEN_WIDTH, SCREEN_HEIGHT}); // Set the view size to the screen size
    view.setCenter({0,0}); // Center the view in the window
}

void GameState::draw(RenderWindow& window) const
{
    switch (current_state)
    {
        case INIT:
            // Draw the title sprite (to be implemented)
            break;
        case RUNNING:
                if(player) // Check if the player object is not null
                {
                    player->draw(window); // Draw the player sprite on the window
                    window.setView(view); // Set the view for the window
                }
            break;
        case PAUSED:
            // Draw the paused state (to be implemented)
            break;
        case STOPPED:
            // Draw the stopped state (to be implemented)
            break;
    }
}

void GameState::update()
{
    // Update player position
    for(int i = 0; i < 4; i++) {
        if(move_directions[i])
            player->update(static_cast<DIRECTIONS>(i)); // Move the player in the specified direction
    }

    // Update the view position to follow the player
    view.setCenter(player->get_position()); // Set the view center to the player's position
}
