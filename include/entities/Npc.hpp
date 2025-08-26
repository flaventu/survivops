#pragma once
#include "Entity.hpp"
#include <cstdlib>
#include <ctime>

// Class to handle non-player characters
class Npc : public Entity
{

    protected:
    
        void animate() override { spriteNum = (spriteNum + 1) % 2; }
        void spawn(const TileMap&);

    public:
    
        sf::Clock moveClock;

        Npc(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const TileMap& tileMap) 
        : Entity(textureFile, frameWidth, frameHeight), moveClock()
        { 
            speed = 4;
            srand(static_cast<unsigned int>(time(0)));
            spawn(tileMap); 
        }

        void move(const Collision&, const sf::View&);

        void draw(sf::RenderWindow& window) const override { if(visible) Entity::draw(window); }

};
