#pragma once
#include "IState.hpp"
#include "../GameState.hpp"

class RunningState : public IState {
    public:

        GameState& gs;

        RunningState(GameState& gameState) : gs(gameState) {}

        void update() override;

        void draw(sf::RenderWindow& window) const override;
};