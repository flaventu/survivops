#pragma once
#include "IState.hpp"

// Start state class
class StartState : public IState {

    public:

        void update() override {}
        void draw(sf::RenderWindow&) const override {}

};
