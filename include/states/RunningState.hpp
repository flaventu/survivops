#pragma once
#include "../GameState.hpp"

// Running state class
class RunningState : public IState {
    
    private:

        GameState& gs;

    public:

        RunningState(GameState& gameState) : gs(gameState) {}

        void update() override;
        void draw(sf::RenderWindow&) const override;
        
};