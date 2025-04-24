#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"

// Aspect ratio of 16:9
inline constexpr float ASPECT = static_cast<float>(MIN_SCREEN_WIDTH)/static_cast<float>(MIN_SCREEN_HEIGHT);

// Function to handle window resize events
void handle_resize (const sf::Event::Resized&, sf::RenderWindow&, sf::Vector2u&); // Handle window resize events

// Template function to handle events
template<typename T>
void handle(const T&, GameState&) {}

void handle(const sf::Event::KeyPressed&, GameState&); // Handle key pressed events
void handle(const sf::Event::KeyReleased&, GameState&); // Handle key released events