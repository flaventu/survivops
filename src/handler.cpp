#include "../include/const.h"
#include "../include/handler.h"
using namespace sf;

void handle_resize (const Event::Resized& resized, sf::RenderWindow& window, Vector2f& last_window_size)
{   
    // Get the new size of the window
    Vector2u ws = resized.size;

    if(ws.x == last_window_size.x && ws.y == last_window_size.y)
        return; // if the size is the same as the last size, do nothing

    // if the new size is smaller than the minimum size, set it to the minimum size
    if(ws.x < MIN_SCREEN_WIDTH || ws.y < MIN_SCREEN_HEIGHT)
        window.setSize({MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT});
    else
    {
        // calculate the new aspect ratio 
        float new_aspect = static_cast<float>(ws.x)/static_cast<float>(ws.y);

        // adjust the size of the window to maintain the aspect ratio (16:9)
        (new_aspect < ASPECT) ? ws = {ws.x,static_cast<unsigned>(ws.x/ASPECT)} : ws = {static_cast<unsigned>(ws.y*ASPECT),ws.y};

        // set the last size of the window to the new size
        last_window_size = {static_cast<float>(ws.x), static_cast<float>(ws.y)};

        // set the new size of the window
        window.setSize(ws);
    }
}

void handle(const Event::KeyPressed& key, GameState& game_state)
{
    // Handle key pressed events
    switch (key.code)
    {
        case Keyboard::Key::Enter:
            game_state.set_state(RUNNING); // Set the game state to RUNNING
            break;
        default:
            break;
    }
}