#pragma once
#include "../const.hpp"

// Interface for game states
class IState {
    public:
        virtual ~IState() = default;
        virtual void update(sf::Clock&) = 0;
        virtual void draw(sf::RenderWindow&) const = 0;
};