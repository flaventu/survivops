#pragma once

#include "state.h"

// Aspect ratio of 16:9
inline constexpr float ASPECT = static_cast<float>(SCREEN_WIDTH)/static_cast<float>(SCREEN_HEIGHT);

// Function prototypes for handling events
void handle_resize (const sf::Event::Resized&, sf::RenderWindow&, sf::Vector2f&, GameState&); // Handle window resize events

// Template function to handle events
template<typename T>
void handle(const T&, GameState&) {}

void handle(const sf::Event::KeyPressed&, GameState&); // Handle key pressed events
void handle(const sf::Event::KeyReleased&, GameState&); // Handle key released events