#pragma once
#include "IState.hpp"

class StartState : public IState {

    void update() override;

    void draw(sf::RenderWindow& window) const override;
};
