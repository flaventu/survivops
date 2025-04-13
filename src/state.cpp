#include "../include/const.h"
#include "../include/state.h"
using namespace sf;
using namespace std;

CURRENT_STATE previous_state = STOPPED; // Previous state of the game
optional<Sprite> title_sprite; // Optional sprite for the title
Texture title_texture; // Texture for the title

void display_title(RenderWindow& window)
{
    // Check if the previous state is not INIT to avoid reloading the texture
    if(previous_state != INIT)  {

        previous_state = INIT; // Set the previous state to INIT

        if(!title_texture.loadFromFile(TITLE_IMAGE)) // Load the title texture
            throw new Exception("Failed to load title texture"); // Throw an exception if the texture cannot be loaded
            
        title_sprite = Sprite(title_texture); // Create a sprite from the texture
        FloatRect bounds = title_sprite.value().getLocalBounds(); // Get the bounds of the sprite
        Vector2f newOrigin(bounds.size.x / 2, bounds.size.y / 2); // Calculate the new origin
        title_sprite.value().setOrigin(newOrigin); // Set the origin to the center of the sprite

        title_sprite.value().setPosition({0,0}); // Center the sprite in the window
    }

    // Draw the title screen
    window.draw(title_sprite.value()); // Draw the title sprite

}

GameState::GameState(RenderWindow& window)
{
    current_state = INIT; // Initialize the game state to INIT
    view.setSize({SCREEN_WIDTH, SCREEN_HEIGHT}); // Set the view size to the screen size
    view.setCenter({0,0}); // Center the view in the window
    window.setView(view); // Set the view for the window
}

void GameState::draw(RenderWindow& window) const
{
    switch (current_state)
    {
        case INIT:
            try {
                display_title(window); // Display the title screen
            } catch (const std::exception& e) {
                throw e; // Throw that exception if there is an error displaying the title
            }
            break;
        case RUNNING:
            // Draw the running state (to be implemented)
            break;
        case PAUSED:
            // Draw the paused state (to be implemented)
            break;
        case STOPPED:
            // Draw the stopped state (to be implemented)
            break;
    }
}

void GameState::update(float elapsed)
{
    // Update the current state (to be implemented)
}
