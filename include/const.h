#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

const std::string TITLE = "SurvivOps"; // Title of the game

const std::string ICON_PATH = "assets/icon.png"; // Path to the game icon

inline constexpr int MAX_FPS = 60; // Frames per second

inline constexpr int ORIGINAL_TILES_SIZE = 16; // Original size of tiles in pixels (16x16)
inline constexpr int SCALE_TILE = 3; // Scale factor for tiles (3x)
inline constexpr int TILE_SIZE = ORIGINAL_TILES_SIZE * SCALE_TILE; // Scaled tile size in pixels (48x48)

inline constexpr int MAX_SCREEN_COLS = 32; // Maximum number of columns on the screen
inline constexpr int MAX_SCREEN_ROWS = 18; // Maximum number of rows on the screen

inline constexpr int SCREEN_WIDTH = TILE_SIZE * MAX_SCREEN_COLS; // Screen width in pixels (1536)
inline constexpr int SCREEN_HEIGHT = TILE_SIZE * MAX_SCREEN_ROWS; // Screen height in pixels (864)

inline constexpr int MIN_SCREEN_COLS = 16; // Minimum number of columns on the screen
inline constexpr int MIN_SCREEN_ROWS = 9; // Minimum number of rows on the screen

inline constexpr int MIN_SCREEN_WIDTH = TILE_SIZE * MIN_SCREEN_COLS; // Minimum screen width in pixels (768)
inline constexpr int MIN_SCREEN_HEIGHT = TILE_SIZE * MIN_SCREEN_ROWS; // Minimum screen height in pixels (480)