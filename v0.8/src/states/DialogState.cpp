#include "../../include/states/DialogState.hpp"
using namespace sf;
using namespace std;

DialogState::DialogState(GameState& gameState, Npc* npc) : gs(gameState), currentNpc(npc), font("assets/fonts/arial.ttf"), dialogueText(font), arrowTexture("assets/ui/arrow.png"), arrowSprite(arrowTexture) {

    // Setup the dialogue text
    dialogueText.setCharacterSize(20);
    dialogueText.setFillColor(Color::White);
    dialogueText.setOutlineColor(Color::Black);
    dialogueText.setOutlineThickness(1);
    
    // Setup the dialogue box
    dialogueBox.setSize({400.f, 80.f});
    dialogueBox.setOrigin({dialogueBox.getSize().x / 2.f, dialogueBox.getSize().y / 2.f});
    dialogueBox.setFillColor(Color(0, 0, 0, 200));
    dialogueBox.setOutlineColor(Color::White);
    dialogueBox.setOutlineThickness(2);
    
    dialogueBox.setPosition({SCREEN_WIDTH / 2.f, 150.f});

    arrowSprite.setPosition({dialogueBox.getPosition().x - dialogueBox.getSize().x / 2.f + 20.f, dialogueBox.getPosition().y - 23.f});
}

void DialogState::advanceDialogue() {

    // Get the next line of dialogue from the NPC
    string dialogue = currentNpc->speak();
    dialogueText.setString(dialogue);

    // Center the text within the dialogue box
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
    gs.player.getWeapon()->draw(window);
    window.draw(dialogueBox);
    window.draw(dialogueText);

    // Draw the arrow sprite if the option is available and a valid answer is present
    if(currentNpc->isOptionAvailable() && currentNpc->getAnswer() >= 0)
        window.draw(arrowSprite);
}

void DialogState::update() {

    // Update the arrow sprite position based on the possible answer
    switch (currentNpc->getAnswer())
    {
    case 0:
        arrowSprite.setPosition({dialogueBox.getPosition().x - dialogueBox.getSize().x / 2.f + 20.f, dialogueBox.getPosition().y - 23.f});
        break;

    case 1:
        arrowSprite.setPosition({dialogueBox.getPosition().x - dialogueBox.getSize().x / 2.f + 20.f, dialogueBox.getPosition().y - 3.f});
        break;
    }
}