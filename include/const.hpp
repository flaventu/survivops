#pragma once

#include <SFML/Graphics.hpp>
#include <string>

const std::string TITLE = "SurvivOps"; // Title of the game

const std::string ICON_PATH = "assets/icon.png"; // Path to the game icon

inline constexpr unsigned int MAX_FPS = 60; // Frames per second
inline constexpr unsigned int TILE_SIZE = 48; // tile size in pixels (48x48)

inline constexpr unsigned int MAX_SCREEN_COLS = 32; // Maximum number of columns on the screen
inline constexpr unsigned int MAX_SCREEN_ROWS = 18; // Maximum number of rows on the screen

inline constexpr unsigned int SCREEN_WIDTH = TILE_SIZE * MAX_SCREEN_COLS; // Screen width in pixels (1536)
inline constexpr unsigned int SCREEN_HEIGHT = TILE_SIZE * MAX_SCREEN_ROWS; // Screen height in pixels (864)

inline constexpr unsigned int MIN_SCREEN_COLS = 16; // Minimum number of columns on the screen
inline constexpr unsigned int MIN_SCREEN_ROWS = 9; // Minimum number of rows on the screen

inline constexpr unsigned int MIN_SCREEN_WIDTH = TILE_SIZE * MIN_SCREEN_COLS; // Minimum screen width in pixels (768)
inline constexpr unsigned int MIN_SCREEN_HEIGHT = TILE_SIZE * MIN_SCREEN_ROWS; // Minimum screen height in pixels (480)

inline constexpr unsigned int WORLD_COLS = 50; // Number of columns in the world
inline constexpr unsigned int WORLD_ROWS = 50; // Number of rows in the world

inline constexpr unsigned int WORLD_WIDTH = TILE_SIZE * WORLD_COLS; // World width in pixels (2400)
inline constexpr unsigned int WORLD_HEIGHT = TILE_SIZE * WORLD_ROWS; // World height in pixels (2400)