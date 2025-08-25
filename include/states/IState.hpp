#pragma once
#include <SFML/Graphics.hpp>

// Interface for game states
class IState {

    public:
    
        virtual ~IState() = default;
        virtual void update() = 0;
        virtual void draw(sf::RenderWindow&) const = 0;

};