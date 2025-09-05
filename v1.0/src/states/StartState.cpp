#include "../../include/states/StartState.hpp"

StartState::StartState() : font("assets/fonts/arial.ttf"), titleTexture("assets/title.png"), titleSprite(titleTexture), titleText(font, "Press Enter to Start", 50), clock() {
    titleSprite.setOrigin({titleTexture.getSize().x / 2.f, titleTexture.getSize().y / 2.f});
    titleSprite.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f});
    titleText.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 175.f});
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
}

void StartState::update() {
    if (clock.getElapsedTime().asSeconds() > 0.85f) {
        titleText.setFillColor(titleText.getFillColor() == sf::Color::White ? sf::Color::Transparent : sf::Color::White);
        clock.restart();
    }
}

void StartState::draw(sf::RenderWindow& window) const {
    window.draw(titleSprite);
    window.draw(titleText);
}