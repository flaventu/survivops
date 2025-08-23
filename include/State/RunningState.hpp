#pragma once
#include "IState.hpp"
#include "../GameState.hpp"

// Running state class
class RunningState : public IState {
    public:

        GameState& gs;

        RunningState(GameState& gameState) : gs(gameState) {}

        void update(sf::Clock&) override;

        void draw(sf::RenderWindow&) const override;
};