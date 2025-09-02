#pragma once
#include "IState.hpp"
#include "../GameState.hpp"

// Paused state class
class PausedState : public IState {

    private:

        GameState& gs;

    public:

        PausedState(GameState& game_state) : gs(game_state) {}

        void update() override;
        void draw(sf::RenderWindow&) const override;
        
};
