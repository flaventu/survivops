#pragma once
#include "IState.hpp"
#include "../const.hpp"

// Start state class
class StartState : public IState {

    private:

        sf::Font font;
        sf::Texture titleTexture;
        sf::Sprite titleSprite;
        sf::Text titleText;
        sf::Clock clock;

    public:

        StartState();

        void update() override;
        void draw(sf::RenderWindow&) const override;

};
