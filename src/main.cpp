#include "../include/const.hpp"
#include "../include/handler.hpp"
#include "../include/state.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int main()
{
    // Set up the window
    RenderWindow window(VideoMode({MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT}), TITLE);
    window.setFramerateLimit(MAX_FPS); // Limit frame rate

    try {

        Image icon(ICON_PATH); // Load the icon image
        window.setIcon(icon); // Set the icon for the window

    } catch (const Exception& e) {

        cerr << "Error loading icon: " << e.what() << endl;
        EXIT_FAILURE; // Exit if the icon cannot be loaded

    }

    Vector2u last_window_size({MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT}); // Last window size

    GameState game_state; // Game state object

    try {
        game_state = GameState(); // Initialize the game state
    }
    catch (const Exception& e) {
        cerr << "Error initializing game state: " << e.what() << endl;
        return EXIT_FAILURE; // Exit if there is an error
    }

    while (window.isOpen())
    {

        // Handle events
        window.handleEvents(
            [&](const Event::Closed& event) { window.close(); }, // close the window
            [&](const Event::Resized& event) { handle_resize(event, window, last_window_size); }, // resize the window
            [&](const auto& event) { handle(event, game_state); } // handle other events
        );
        
        // Update the game state
        game_state.update();
            
        // Clear the window
        window.clear();
            
        // Draw the game state
        game_state.draw(window);
            
        // Display the window contents
        window.display();
    }
}
