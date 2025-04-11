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
        last_window_size.x = ws.x;
        last_window_size.y = ws.y;

        // set the new size of the window
        window.setSize(ws);
    }
}

void handle_fullscreen(const Event::KeyPressed& key, sf::RenderWindow& window, bool& fullscreen)
{

    // Check if the size of the desktop has an aspect ratio of 16:9
    if(static_cast<float>(DESKTOP.size.x) / static_cast<float>(DESKTOP.size.y) == ASPECT)
    {

        // if that size has an aspect ratio of 16:9, check if the key pressed is F11
        if(key.code == Keyboard::Key::F11)
        {
            // if the window is in fullscreen mode, create a window with the original size
            if (fullscreen)
            {
                window.create(VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), TITLE, Style::Default);
                window.setFramerateLimit(MAX_FPS); // Limit frame rate to FPS
                fullscreen = false; // Reset fullscreen mode flag
            }

            // else create a fullscreen window
            else
            {
                window.create(DESKTOP, TITLE, Style::None);
                window.setFramerateLimit(MAX_FPS); // Limit frame rate to FPS
                fullscreen = true; // Set fullscreen mode flag
            }
        }
    }
}