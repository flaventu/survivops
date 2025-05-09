#pragma once
#include "entity.hpp"

// Class to handle the player character
class Player : public Entity
{
    private:

        void loadTextures() override; // Load textures for the player sprite

    public:

        Player(); // Constructor to initialize the player sprite
};
