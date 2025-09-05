#include "../../include/states/RunningState.hpp"
using namespace sf;

void RunningState::update() {

    // Update player position
    for(int i = 0; i < 4; i++) {
        
        if(gs.move_directions[i])
        {
            
            gs.player.update(static_cast<DIRECTIONS>(i), gs.collision);

            // Update the view position to follow the player
            gs.view.setCenter(gs.player.get_position());

            // Update the tilemap to match the view
            gs.tilemap.update(gs.view);
        }
    }

    gs.ui.update(gs.player);

}

void RunningState::draw(RenderWindow& window) const {
    
    window.setView(gs.view); // Set the view for the window

    // Draw the running state
    window.draw(gs.tilemap);
    gs.player.draw(window);

    window.setView(window.getDefaultView());
    gs.ui.draw(window);
}
