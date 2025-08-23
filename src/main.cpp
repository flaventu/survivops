#include "../include/handler.hpp"
#include <iostream>
using namespace sf;
using namespace std;

int main()
{
    // Set up the window
    RenderWindow window(VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), TITLE);
    window.setFramerateLimit(MAX_FPS); // Limit frame rate

    try {

        Image icon(ICON_PATH); // Load the icon image
        window.setIcon(icon); // Set the icon for the window

    } catch (const Exception& e) {

        cerr << "Error loading icon: " << e.what() << endl;
        EXIT_FAILURE; // Exit if the icon cannot be loaded

    }

    Vector2u last_window_size({SCREEN_WIDTH, SCREEN_HEIGHT}); // Last window size

    // TO BE CHANGED (now we start with the RunningState instead of the StartState)
    GameState game_state(std::make_unique<StartState>());

    Clock clock; // Clock for managing time
    
    while (window.isOpen())
    {

        // Handle events
        window.handleEvents(
            [&](const Event::Closed& event) { window.close(); }, // close the window
            [&](const Event::Resized& event) { handle_resize(event, window, last_window_size); }, // resize the window
            [&](const auto& event) { handle(event, game_state); } // handle other events
        );
        
        // Update the game state
        game_state.update(clock);

        // Clear the window
        window.clear();
            
        // Draw the game state
        game_state.draw(window);
            
        // Display the window contents
        window.display();
    }
}
