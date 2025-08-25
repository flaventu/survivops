#pragma once
#include "states/StartState.hpp"
#include "states/RunningState.hpp"

// Handler class to manage game states
class Handler {

    private:

        Handler() = default;

        static inline constexpr float ASPECT = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);

        // Util
        static void resizeWindow(sf::Vector2u&, sf::Vector2u&, sf::RenderWindow&);
        static void handleEnterPressed(GameState&);


    public:

        static void handle_resize (const sf::Event::Resized&, sf::RenderWindow&, sf::Vector2u&);

        template<typename T>
        static void handle(const T&, GameState&) {}
        static void handle(const sf::Event::KeyPressed&, GameState&);
        static void handle(const sf::Event::KeyReleased&, GameState&);

};