#pragma once
#include "State/IState.hpp"
#include "State/StartState.hpp"
#include "Player.hpp"
#include "Tilemap.hpp"
#include "UI.hpp"


// Class to handle the game state
class GameState
{

    public:

        std::unique_ptr<IState> state; // Pointer to the current state of the game (using smart pointers for automatic memory management)
        sf::View view;
        Player player;
        TileMap tilemap;
        UI ui;

        GameState(std::unique_ptr<IState>);

        bool move_directions[4] = {false,false,false,false}; // Array to store movement directions

        // Getters
        sf::View get_view() const { return view; }
        IState& getState() const { return *state; }

        // Setters
        void set_view(const sf::View& v) { view = v; }
        void changeState(std::unique_ptr<IState> newState) { state = std::move(newState); }

        void draw(sf::RenderWindow& window) const { state->draw(window); }
        void update() { state->update(); }
};

