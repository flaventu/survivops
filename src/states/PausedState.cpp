#include "../../include/states/PausedState.hpp"
using namespace sf;

PausedState::PausedState(GameState& game_state) : gs(game_state), font("assets/fonts/arial.ttf"), pausedText(font), instructionText(font)
{

    stopAllClocks();

    pausedText.setString("Game Paused");
    pausedText.setCharacterSize(48);
    pausedText.setFillColor(Color::White);
    pausedText.setStyle(Text::Bold | Text::Underlined);
    pausedText.setOutlineColor(Color::Black);
    pausedText.setOutlineThickness(2.f);
    pausedText.setOrigin({pausedText.getLocalBounds().size.x / 2, pausedText.getLocalBounds().size.y / 2});
    pausedText.setPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4});

    background.setSize({SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.65f});
    background.setOrigin(background.getSize() / 2.f);
    background.setFillColor(Color(0, 0, 0, 150)); // Semi-transparent black
    background.setOutlineColor(Color::White);
    background.setOutlineThickness(3.f);
    background.setPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

    std::string instructionStr = "ESC - to Resume\n";
    (gs.tilemap->isFightable()) ? instructionStr += "  H   - to go Home\n" : instructionStr += "  F   - to Fight in the Arena\n";

    instructionText.setString(instructionStr);
    instructionText.setCharacterSize(30);
    instructionText.setFillColor(Color::White);
    instructionText.setStyle(Text::Italic);
    instructionText.setOutlineColor(Color::Black);
    instructionText.setOutlineThickness(1.5f);
    instructionText.setLineSpacing(1.5f);
    instructionText.setOrigin({instructionText.getLocalBounds().size.x / 2, instructionText.getLocalBounds().size.y / 2});
    instructionText.setPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

}

void PausedState::update()
{

}

void PausedState::draw(RenderWindow& window) const
{
    window.setView(gs.view);

    window.draw(*gs.tilemap.get());

    for(const auto& entity : gs.drawable_entities) {
        entity->draw(window);
    }

    window.setView(window.getDefaultView());
    gs.ui.draw(window);
    gs.player.getWeapon().draw(window);

    window.draw(background);
    window.draw(pausedText);
    window.draw(instructionText);
}

void PausedState::stopAllClocks()
{
    if(gs.tilemap->isFightable()) {
        gs.tilemap->stopSpawnClock();
    }
    gs.player.stopAllClocks();
    for(const auto& entity : gs.drawable_entities) {
        entity->stopAllClocks();
    }
}

void PausedState::resume()
{
    if(gs.tilemap->isFightable()) {
        gs.tilemap->restartSpawnClock();
    }
    gs.player.restartAllClocks();
    for(const auto& entity : gs.drawable_entities) {
        entity->restartAllClocks();
    }
}
