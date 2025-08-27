#pragma once
#include "../GameState.hpp"

// Dialog state class
class DialogState : public IState {

    private:

        GameState& gs;
        Npc* currentNpc;

        sf::Font font;
        sf::Text dialogueText;

        sf::RectangleShape dialogueBox;

    public:

        DialogState(GameState& gameState, Npc* npc);

        void advanceDialogue();
        Npc* getCurrentNpc() const { return currentNpc; }

        void update() override {}
        void draw(sf::RenderWindow&) const override;
        
};