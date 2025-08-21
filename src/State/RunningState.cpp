#include "../../include/State/RunningState.hpp"

void RunningState::update() {
    
    // Update player position
    for(int i = 0; i < 4; i++) {
        if(gs.move_directions[i])
            gs.player.update(static_cast<DIRECTIONS>(i), gs.tilemap); // Move the player in the specified direction
    }

    while (!gs.tilemap.pickableObjects.empty())
    {
        gs.player.addToInventory(gs.tilemap.pickableObjects.back());
        gs.tilemap.pickableObjects.pop_back(); // Remove the object from the pickable objects vector
    }

    gs.ui.update(gs.player.getHealthPerc(), gs.player.getMoney() ,gs.player.getExpPerc(), gs.player.getCurrentLevel() ,gs.view, gs.player.getInventory());

    // Update the view position to follow the player
    gs.view.setCenter(gs.player.get_position()); // Set the view center to the player's position

    // Update the tilemap to match the view
    gs.tilemap.update(gs.view); // Update the tilemap with the current view
}

void RunningState::draw(sf::RenderWindow& window) const {
    
    // Draw the running state
    window.draw(gs.tilemap);
    gs.player.draw(window);
    gs.ui.draw(window);
    window.setView(gs.view); // Set the view for the window
}
