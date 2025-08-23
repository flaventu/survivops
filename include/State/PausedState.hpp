#pragma once
#include "IState.hpp"

// Paused state class
class PausedState : public IState {

    void update(sf::Clock&) override;

    void draw(sf::RenderWindow&) const override;
};
