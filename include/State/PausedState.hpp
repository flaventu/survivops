#pragma once
#include "IState.hpp"

class PausedState : public IState {

    void update() override;

    void draw(sf::RenderWindow& window) const override;
};
