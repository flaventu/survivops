#pragma once
#include "IState.hpp"
#include "../GameState.hpp"

// Death state class
class DeathState : public IState {

    private:

        GameState& gs;

        sf::Font font;
        sf::Text deathText;
        sf::RectangleShape background;
        sf::Text instructionText;

    public:

        DeathState(GameState& game_state);

        void respawn();

        void update() override;
        void draw(sf::RenderWindow&) const override;
        
};
