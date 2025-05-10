#pragma once
#include "const.hpp"
#include "state.hpp"

// Aspect ratio of 1.5
inline constexpr float ASPECT = static_cast<float>(SCREEN_WIDTH)/static_cast<float>(SCREEN_HEIGHT);

// Function to handle window resize events
void handle_resize (const sf::Event::Resized&, sf::RenderWindow&, sf::Vector2u&); // Handle window resize events

void resizeWindow(sf::Vector2u &ws, sf::Vector2u & last_window_size, sf::RenderWindow & window);

// Template function to handle events
template<typename T>
void handle(const T&, GameState&) {}

void handle(const sf::Event::KeyPressed&, GameState&); // Handle key pressed events
void handle(const sf::Event::KeyReleased&, GameState&); // Handle key released events

void handleEnter(GameState&); // Handle enter key events