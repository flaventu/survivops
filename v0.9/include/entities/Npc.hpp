#pragma once
#include "../Collision.hpp"
#include "Entity.hpp"

// Class to handle non-player characters
class Npc : public Entity
{
    protected:

        // Dialogue
        std::vector<std::vector<std::string>> dialogue;
        int currentDialogueIndex = 0;
        int currentMessage = 0;
        bool inDialogue = false;
        int answer = 0;
        bool optionAvailable = false;
        void nextDialogue();
        virtual void loadDialogue() = 0;
        
        // Animation
        void animate() override { spriteNum = (spriteNum + 1) % 2; }
        
        // Movement
        sf::Clock moveClock;

    public:
        
        Npc(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight) 
        : Entity(textureFile, frameWidth, frameHeight), moveClock()
            { speed = 4; }

        // Getters
        const int getAnswer() const { return answer; }
        bool isOptionAvailable() const { return optionAvailable; }

        // Setters
        void setAnswer(int newAnswer) { answer = newAnswer; }
        void setOptionAvailable(bool available) { optionAvailable = available; }

        // Dialogue
        virtual std::string speak();
        const bool isInDialogue() const { return inDialogue; }
        void startDialogue() { inDialogue = true; currentDialogueIndex = 0; }

        void update(const Collision&, const sf::View&, const sf::FloatRect&);

};
