#include "../../include/entities/Npc.hpp"
using namespace std;
using namespace sf;

void Npc::update(const Collision& collision, const sf::View& view, const FloatRect& playerHitbox)
{

    int timeElapsed = moveClock.getElapsedTime().asMilliseconds();

    if(timeElapsed > 600 && timeElapsed % 200 < 15) {

        Vector2f newPosition = position;

        switch (direction)
        {
            case UP: newPosition.y -= speed; break;
            case DOWN: newPosition.y += speed; break;
            case LEFT: newPosition.x -= speed; break;
            case RIGHT: newPosition.x += speed; break;
            default: break;
        }

        if(!collision.collision(getHitbox(), direction, speed))
        {
            if(!isVisible() || !collision.collision(getHitbox(), direction, speed, playerHitbox))
            {
                position = newPosition; // Update the position if there is no collision

                animate();
            }
        }

        // Update the entity sprite position
        entitySprite.setPosition(position);
        entityHitbox.position = {position.x - (HITBOX_SIZE / 2), position.y - (HITBOX_SIZE / 2) + HITBOX_OFFSET}; // Set the position of the entity hitbox
        updateTextureRect();

        // Change direction randomly after a certain period
        if(timeElapsed > 1200)
        {
            direction = static_cast<DIRECTIONS>(rand() % 4);
            moveClock.restart();
        }
    }

    // Update the NPC's visibility based on the camera view
    updateVisibility(view);
}

string Npc::speak() { 

    string message = dialogue[currentMessage][currentDialogueIndex++];
    nextDialogue();
    return message;
    
}

void Npc::nextDialogue() {
    if(currentDialogueIndex == dialogue[currentMessage].size())
    {
        inDialogue = false;
        if(currentMessage < dialogue.size() - 1)
            currentMessage++;
    }
}