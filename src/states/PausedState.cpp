#include "../../include/states/PausedState.hpp"
using namespace sf;

void PausedState::update()
{
    // Update the paused state
}

void PausedState::draw(RenderWindow& window) const
{
    window.setView(gs.view);

    window.draw(gs.tilemap);

    for(const auto& entity : gs.drawable_entities) {
        entity->draw(window);
    }

    window.setView(window.getDefaultView());
    gs.ui.draw(window);
    gs.player.getWeapon().draw(window);
}