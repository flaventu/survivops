#pragma once
#include "IState.hpp"
#include "../const.hpp"

// Start state class
class StartState : public IState {

    private:

        sf::Texture titleTexture;
        sf::Sprite titleSprite;
        sf::Font font;
        sf::Text titleText;
        sf::Clock clock;

    public:

        StartState();

        void update() override;
        void draw(sf::RenderWindow&) const override;

};
