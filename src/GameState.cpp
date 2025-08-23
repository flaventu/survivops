#include "../include/GameState.hpp"
using namespace sf;


GameState::GameState(std::unique_ptr<IState> init) : state(std::move(init)), player(), tilemap(), view(), ui() // Initialize the player and view objects
{
    view.setSize({SCREEN_WIDTH, SCREEN_HEIGHT}); // Set the view size to the screen size
    view.setCenter({0,0}); // Center the view in the window

    if(!tilemap.load("../../assets/maps/map1.png", "../../assets/maps/map1.csv",5)) // Load the tilemap
        throw new Exception("Failed to load tilemap"); // Throw an exception if the tilemap fails to load

    if(!tilemap.loadObjects("../../assets/objects/obj_map1.csv")) // Load the objects in the tilemap
        throw new Exception("Failed to load objects"); // Throw an exception if the objects fail to load
}
