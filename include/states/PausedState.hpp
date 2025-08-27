#pragma once
#include "IState.hpp"

// Paused state class
class PausedState : public IState {

    public:

        void update() override {}
        void draw(sf::RenderWindow&) const override {}
        
};
