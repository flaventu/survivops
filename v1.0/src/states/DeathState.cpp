#include "../../include/states/DeathState.hpp"
using namespace sf;

DeathState::DeathState(GameState& game_state) : gs(game_state), font("assets/fonts/arial.ttf"), deathText(font), instructionText(font)
{

    deathText.setString("Game Over");
    deathText.setCharacterSize(48);
    deathText.setFillColor(Color::White);
    deathText.setStyle(Text::Bold | Text::Underlined);
    deathText.setOutlineColor(Color::Black);
    deathText.setOutlineThickness(2.f);
    deathText.setOrigin({deathText.getLocalBounds().size.x / 2, deathText.getLocalBounds().size.y / 2});
    deathText.setPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4});

    background.setSize({SCREEN_WIDTH * 0.65, SCREEN_HEIGHT * 0.65});
    background.setOrigin(background.getSize() / 2.f);
    background.setFillColor(Color(255, 0, 0, 150)); // Semi-transparent red
    background.setOutlineColor(Color::White);
    background.setOutlineThickness(3.f);
    background.setPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

    std::string instructionStr = "R - to Respawn\n";

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

void DeathState::update()
{

}

void DeathState::draw(RenderWindow& window) const
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
    window.draw(deathText);
    window.draw(instructionText);
}

void DeathState::respawn()
{
    gs.changeMap("assets/maps/main.png", "assets/maps/main.csv", 8, false);
    gs.player.respawn();
}
