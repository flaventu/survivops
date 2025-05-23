#include "../include/handler.hpp"
using namespace sf;

void handle_resize (const Event::Resized& resized, RenderWindow& window, Vector2u& last_window_size)
{   
    // Get the new size of the window
    Vector2u ws = resized.size;

    if(ws.x == last_window_size.x && ws.y == last_window_size.y)
        return; // if the size is the same as the last size, do nothing

    // if the new size is smaller than the minimum size, set it to the minimum size
    if(ws.x < MIN_SCREEN_WIDTH || ws.y < MIN_SCREEN_HEIGHT)
        window.setSize({MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT});
    else if(ws.x > MAX_SCREEN_WIDTH || ws.y > MAX_SCREEN_HEIGHT)
        window.setSize({MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT});
    else
        resizeWindow(ws, last_window_size, window);
}


void resizeWindow(sf::Vector2u &ws, sf::Vector2u & last_window_size, sf::RenderWindow & window)
{
        // casting to float
        float x_float = static_cast<float>(ws.x);
        float y_float = static_cast<float>(ws.y);
        
        // calculate the new aspect ratio 
        float new_aspect = x_float/y_float;

        // adjust the size of the window to maintain the aspect ratio 1.5
        (new_aspect < ASPECT) ? ws = {ws.x,static_cast<unsigned>(ws.x/ASPECT)} : ws = {static_cast<unsigned>(ws.y*ASPECT),ws.y};

        // set the last size of the window to the new size
        last_window_size = {ws.x, ws.y};

        // set the new size of the window
        window.setSize(ws);
}


void handle(const Event::KeyPressed& key, GameState& game_state)
{
    // Handle key pressed events
    switch (key.code)
    {

        case Keyboard::Key::Enter:

            handleEnter(game_state); // Handle enter key events
            break;

        case Keyboard::Key::W:
                game_state.move_directions[UP] = true; // Set the UP direction to true
            break;

        case Keyboard::Key::S:
                game_state.move_directions[DOWN] = true; // Set the UP direction to true
            break;

        case Keyboard::Key::A:
                game_state.move_directions[LEFT] = true; // Set the UP direction to true
            break;

        case Keyboard::Key::D:
                game_state.move_directions[RIGHT] = true; // Set the UP direction to true
            break;
    }
}

void handleEnter(GameState& game_state)
{
    // Handle enter key events based on the current game state
    switch (game_state.get_state())
    {
        case INIT:
            game_state.set_state(RUNNING); // Set the game state to RUNNING
        break;
    }
}

void handle(const Event::KeyReleased& key, GameState& game_state)
{
    // Handle key released events
    switch (key.code)
    {
        case Keyboard::Key::W:
                game_state.move_directions[UP] = false; // Set the UP direction to false
            break;

        case Keyboard::Key::S:
                game_state.move_directions[DOWN] = false; // Set the UP direction to false
            break;

        case Keyboard::Key::A:
                game_state.move_directions[LEFT] = false; // Set the UP direction to false
            break;

        case Keyboard::Key::D:
                game_state.move_directions[RIGHT] = false; // Set the UP direction to false
            break;
    }
}