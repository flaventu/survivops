#pragma once
#include "IState.hpp"
#include "../GameState.hpp"

// Paused state class
class PausedState : public IState {

    private:

        GameState& gs;

        sf::Font font;
        sf::Text pausedText;
        sf::RectangleShape background;
        sf::Text instructionText;

        void stopAllClocks();

    public:

        PausedState(GameState& game_state);

        void resume();

        void update() override;
        void draw(sf::RenderWindow&) const override;
        
};
