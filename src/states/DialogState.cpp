#include "../../include/states/DialogState.hpp"
using namespace sf;
using namespace std;

DialogState::DialogState(GameState& gameState, Npc* npc) : gs(gameState), currentNpc(npc), font("../../assets/fonts/arial.ttf"), dialogueText(font) {

    // Setup the dialogue text
    dialogueText.setCharacterSize(20);
    dialogueText.setFillColor(Color::White);
    dialogueText.setOutlineColor(Color::Black);
    dialogueText.setOutlineThickness(1);
    
    // Setup the dialogue box
    dialogueBox.setSize({350.f, 80.f});
    dialogueBox.setOrigin({dialogueBox.getSize().x / 2.f, dialogueBox.getSize().y / 2.f});
    dialogueBox.setFillColor(Color(0, 0, 0, 200)); // Semi-transparent black
    dialogueBox.setOutlineColor(Color::White);
    dialogueBox.setOutlineThickness(2);
    
    dialogueBox.setPosition({SCREEN_WIDTH / 2.f, 150.f}); // Position at the bottom of the screen
}

void DialogState::advanceDialogue() {
    string dialogue = currentNpc->speak();

    dialogueText.setString(dialogue);

    dialogueText.setOrigin({dialogueText.getLocalBounds().size.x / 2.f, dialogueText.getLocalBounds().size.y / 2.f});
    dialogueText.setPosition({dialogueBox.getPosition().x + 10.f, dialogueBox.getPosition().y});
}

void DialogState::draw(RenderWindow& window) const {
    
    window.setView(gs.view); // Set the view for the window

    // Draw the running state
    window.draw(gs.tilemap);

    for(const auto& entity : gs.drawable_entities) {
        entity->draw(window);
    }

    window.setView(window.getDefaultView());
    gs.ui.draw(window);
    window.draw(dialogueBox);
    window.draw(dialogueText);
}
