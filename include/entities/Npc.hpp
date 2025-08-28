#pragma once
#include "../Collision.hpp"
#include "Entity.hpp"
#include <cstdlib>
#include <ctime>

// Class to handle non-player characters
class Npc : public Entity
{
    protected:

        // Dialogue
        int currentDialogueIndex = 0;
        int currentMessage = 0;
        bool inDialogue = false;
        virtual void loadDialogue() = 0;
        
        // Animation
        void animate() override { spriteNum = (spriteNum + 1) % 2; }
        
        // Movement
        sf::Clock moveClock;
        void spawn(const TileMap&);
        
    protected:

        std::vector<std::vector<std::string>> dialogue;

    public:
        
        Npc(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const TileMap& tileMap) 
        : Entity(textureFile, frameWidth, frameHeight), moveClock()
        { 
            speed = 4;
            spawn(tileMap); 
        }

        // Dialogue
        int answer = 0;
        bool optionAvailable = false;

        virtual std::string speak();
        const bool isInDialogue() const { return inDialogue; }
        void startDialogue() { inDialogue = true; currentDialogueIndex = 0; }

        void update(const Collision&, const sf::View&, const sf::FloatRect&);
        void draw(sf::RenderWindow& window) const override { if(visible) Entity::draw(window); }

};
