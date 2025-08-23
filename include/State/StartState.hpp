#pragma once
#include "IState.hpp"

// Start state class
class StartState : public IState {

    void update() override;

    void draw(sf::RenderWindow&) const override;
};
