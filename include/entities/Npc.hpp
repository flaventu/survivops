#pragma once
#include "Entity.hpp"
#include "../Collision.hpp"
#include <cstdlib>
#include <ctime>

// Class to handle non-player characters
class Npc : public Entity
{

    protected:

        int currentDialogueIndex = 0;
        std::vector<std::string> dialogue;
        bool inDialogue = false;

        void animate() override { spriteNum = (spriteNum + 1) % 2; }
        void spawn(const TileMap&);

        virtual void loadDialogue() {}
        
    public:
        
        sf::Clock moveClock;
        
        Npc(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const TileMap& tileMap) 
        : Entity(textureFile, frameWidth, frameHeight), moveClock()
        { 
            speed = 4;
            srand(static_cast<unsigned int>(time(0)));
            spawn(tileMap); 
        }

        std::string speak();
        const bool isInDialogue() const { return inDialogue; }
        void startDialogue() { inDialogue = true; currentDialogueIndex = 0; }

        void update(const Collision&, const sf::View&, const sf::FloatRect&);
        void draw(sf::RenderWindow& window) const override { if(visible) Entity::draw(window); }

};
