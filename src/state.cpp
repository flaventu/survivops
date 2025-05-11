#include "../include/state.hpp"
using namespace sf;


GameState::GameState() : player(new Player()), tilemap(new TileMap()) , view(), ui(new UI()) // Initialize the player and view objects
{
    view.setSize({SCREEN_WIDTH, SCREEN_HEIGHT}); // Set the view size to the screen size
    view.setCenter({0,0}); // Center the view in the window

    if(!tilemap->load("../../assets/maps/map1.png", "../../assets/maps/map1.csv",5)) // Load the tilemap
        throw new Exception("Failed to load tilemap"); // Throw an exception if the tilemap fails to load

    if(!tilemap->loadObjects("../../assets/objects/obj_map1.csv")) // Load the objects in the tilemap
        throw new Exception("Failed to load objects"); // Throw an exception if the objects fail to load
}

void GameState::draw(RenderWindow& window) const
{
    switch (current_state)
    {
        case INIT:
            // Draw the title sprite (to be implemented)            
            break;
        case RUNNING:
                if(player && tilemap) // Check if the player object is not null
                {
                    window.draw(*tilemap); // Draw the tilemap on the window
                    player->draw(window); // Draw the player sprite on the window
                    ui->draw(window);
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
            player->update(static_cast<DIRECTIONS>(i), *tilemap); // Move the player in the specified direction
    }

    while (!tilemap->pickableObjects.empty())
    {
        player->addToInventory(tilemap->pickableObjects.back());
        tilemap->pickableObjects.pop_back(); // Remove the object from the pickable objects vector
    }

    ui->update(player->getHealthPerc(), player->getMoney() ,player->getExpPerc(), player->getCurrentLevel() ,view, player->getInventory());
    

    // Update the view position to follow the player
    view.setCenter(player->get_position()); // Set the view center to the player's position

    // Update the tilemap to match the view
    tilemap->update(view); // Update the tilemap with the current view
}
