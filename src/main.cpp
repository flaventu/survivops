#include "../include/const.h"
#include "../include/handler.h"
using namespace sf;

int main()
{
    // Set up the window
    auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), TITLE);
    window.setFramerateLimit(MAX_FPS); // Limit frame rate
    bool fullscreen = false; // Fullscreen mode flag
    Vector2f last_window_size = {SCREEN_WIDTH, SCREEN_HEIGHT}; // Last window size

    while (window.isOpen())
    {

        // Handle events
        window.handleEvents(
            [&](const Event::Closed& event) { window.close(); }, // close the window
            [&window, &last_window_size](const Event::Resized& event) { handle_resize(event, window, last_window_size); }, // resize the window
            [&window, &fullscreen](const Event::KeyPressed& event) { handle_fullscreen(event, window, fullscreen); } // toggle fullscreen
        );

        // Clear the window
        window.clear();

        // Display the window contents
        window.display();
    }
}
