#include "../../include/State/RunningState.hpp"
using namespace sf;

void RunningState::update() {

    // Update player position
    for(int i = 0; i < 4; i++) {
        if(gs.move_directions[i])
            gs.player.update(static_cast<DIRECTIONS>(i), gs.tilemap); // Move the player in the specified direction
    }

    gs.ui.update(gs.player.getHealthPerc(), gs.player.getMoney() ,gs.player.getExpPerc(), gs.player.getCurrentLevel() ,gs.view);

    // Update the view position to follow the player
    gs.view.setCenter(gs.player.get_position());

    // Update the tilemap to match the view
    gs.tilemap.update(gs.view);
}

void RunningState::draw(sf::RenderWindow& window) const {
    
    // Draw the running state
    window.draw(gs.tilemap);
    gs.player.draw(window);
    gs.ui.draw(window);
    window.setView(gs.view); // Set the view for the window
}
