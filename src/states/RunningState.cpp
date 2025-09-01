#include "../../include/states/RunningState.hpp"
using namespace sf;

void RunningState::update() {

    // Update weapon state
    gs.player.getWeapon().update();

    // Handle player attack
    if(gs.player.isAttacking) {
        gs.player.attack();
    }

    // Update player position
    for(int i = 0; i < 4; i++) {
        
        if(gs.move_directions[i])
        {
            
            gs.player.update(static_cast<DIRECTIONS>(i), gs.collision, gs.tilemap.entities);

            // Update the view position to follow the player
            gs.view.setCenter(gs.player.get_position());
        }
    }
    
    // Update the tilemap to match the view
    gs.tilemap.update(gs.view);

    // Update entities
    if(!gs.tilemap.isFightable()) {
        // Update NPCs
        for(auto& entity : gs.tilemap.entities)
                dynamic_cast<Npc&>(*entity.get()).update(gs.collision, gs.view, gs.player.getHitbox());
    } else {
        // Update monsters
        for(auto& entity : gs.tilemap.entities)
            dynamic_cast<Monster&>(*entity.get()).update(gs.tilemap.positionToTile(gs.player.getPosition()), gs.view);
    }

    gs.tilemap.entities.erase(
        remove_if(gs.tilemap.entities.begin(), gs.tilemap.entities.end(),
            [](const std::shared_ptr<Entity>& entity) {
                if(Monster* monster = dynamic_cast<Monster*>(entity.get())) {
                    return monster->getHealth() <= 0;
                }
                return false;
            }),
        gs.tilemap.entities.end()
    );

    gs.loadDrawableEntities();

    // Sort the drawable entities based on their Y position
    sort(gs.drawable_entities.begin(), gs.drawable_entities.end(), [](const Entity* a, const Entity* b) {
        return a->get_position().y < b->get_position().y;
    });

    gs.ui.update(gs.player);

}

void RunningState::draw(RenderWindow& window) const {
    
    window.setView(gs.view);

    window.draw(gs.tilemap);

    for(const auto& entity : gs.drawable_entities) {
        entity->draw(window);
    }

    window.setView(window.getDefaultView());
    gs.ui.draw(window);
    gs.player.getWeapon().draw(window);
}
