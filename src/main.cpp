#include "../include/const.h"
#include "../include/handler.h"
#include "../include/state.h"
#include <iostream>
using namespace sf;

int main()
{
    // Set up the window
    auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), TITLE);
    window.setFramerateLimit(MAX_FPS); // Limit frame rate

    try {

        sf::Image icon(ICON_PATH); // Load the icon image
        window.setIcon(icon); // Set the icon for the window

    } catch (const std::exception& e) {

        std::cerr << "Error loading icon: " << e.what() << std::endl;
        EXIT_FAILURE; // Exit if the icon cannot be loaded

    }

    Vector2f last_window_size = {SCREEN_WIDTH, SCREEN_HEIGHT}; // Last window size

    GameState game_state(window); // Game state object
    Clock clock; // Clock for timing

    while (window.isOpen())
    {

        // Handle events
        window.handleEvents(
            [&](const Event::Closed& event) { window.close(); }, // close the window
            [&](const Event::Resized& event) { handle_resize(event, window, last_window_size, game_state); }, // resize the window
            [&](const auto& event) { handle(event, game_state); } // handle other events
        );
        
        try {
            // Update the game state
            game_state.update(clock.restart().asSeconds()); // Update the game state with the elapsed time
            
            // Clear the window
            window.clear();
            
            // Draw the game state
            game_state.draw(window);
            
            // Display the window contents
            window.display();

        } catch (const Exception& e) {
            std::cerr << "Error: " << e.what() << std::endl; // Print the error message
            return EXIT_FAILURE; // Exit if there is an error
        }
    }
}
