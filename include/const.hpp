#pragma once
#include <SFML/Graphics.hpp>
#include <string>

inline const std::string TITLE = "SurvivOps"; // Title of the game

inline const std::string ICON_PATH = "../../assets/icon.png"; // Path to the game icon

inline constexpr unsigned int MAX_FPS = 60; // Frames per second
inline constexpr unsigned int TILE_SIZE = 48; // tile size in pixels (48x48)

inline constexpr unsigned int SCREEN_COLS = 24; // Number of columns on the screen (24)
inline constexpr unsigned int SCREEN_ROWS = 16; // Number of rows on the screen (16)

inline constexpr unsigned int SCREEN_WIDTH = TILE_SIZE * SCREEN_COLS; // Screen width in pixels (1152)
inline constexpr unsigned int SCREEN_HEIGHT = TILE_SIZE * SCREEN_ROWS; // Screen height in pixels (768)

inline constexpr unsigned int MAX_SCREEN_COLS = 27; // Maximum number of columns on the screen 
inline constexpr unsigned int MAX_SCREEN_ROWS = 18; // Maximum number of rows on the screen

inline constexpr unsigned int MAX_SCREEN_WIDTH = TILE_SIZE * MAX_SCREEN_COLS; // Maximum screen width in pixels (1296)
inline constexpr unsigned int MAX_SCREEN_HEIGHT = TILE_SIZE * MAX_SCREEN_ROWS; // Maximum screen height in pixels (864)

inline constexpr unsigned int MIN_SCREEN_COLS = 18; // Minimum number of columns on the screen
inline constexpr unsigned int MIN_SCREEN_ROWS = 12; // Minimum number of rows on the screen

inline constexpr unsigned int MIN_SCREEN_WIDTH = TILE_SIZE * MIN_SCREEN_COLS; // Minimum screen width in pixels (864)
inline constexpr unsigned int MIN_SCREEN_HEIGHT = TILE_SIZE * MIN_SCREEN_ROWS; // Minimum screen height in pixels (576)

enum DIRECTIONS
{
    DOWN,
    UP,
    LEFT,
    RIGHT,
};

inline constexpr unsigned int HITBOX_SIZE = TILE_SIZE - 16; // Hitbox size in pixels (32x32)
inline constexpr unsigned int HITBOX_OFFSET = TILE_SIZE / 2 - HITBOX_SIZE / 2; // Hitbox offset in pixels (8)