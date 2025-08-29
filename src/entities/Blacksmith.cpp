#include "../../include/entities/Blacksmith.hpp"
using namespace std;

void Blacksmith::loadDialogue() {

    dialogue = {
        {
            "Hey, traveler!",
            "I can help you upgrade your weapons.",
            "Just bring me some coins!"
        },
        {
            "Do you need an upgrade?",
            "It would cost you ... coins.",
            "- Yes\n- No"
        }
    };
}

string Blacksmith::speak() {

    // Update the dialogue with the current price
    dialogue[1][1] = "It would cost you " + to_string(findPrice()) + " coins.";

    // Check if the player's weapon is at max level
    if(player.getWeapon()->getLevel() == player.getWeapon()->getMaxLevel())
    {
        inDialogue = false;
        return "Looks like you don't need me.";
    }

    // Retrieve the current message
    string message = dialogue[currentMessage][currentDialogueIndex++];

    // Check if the message is a dialogue option
    if(message.substr(0,1) == ("-"))
    {
        optionAvailable = true;
        switch (answer)
        {
        case 0:

            // Logic for upgrading the weapon
            if(player.getMoney() < findPrice()) {
                message = "You need " + to_string(findPrice() - player.getMoney()) + " more coins!";
            } else {
                message = "Great! I'll upgrade your weapon.";
                player.payMoney(findPrice());
                player.getWeapon()->upgradeWeapon();
            }
            break;

        case 1:
            message = "Maybe next time...";
            break;
        default:
            currentDialogueIndex--; // stay on the same message
            return message;
            break;
        }
        
        answer = -1;
        inDialogue = false;
        optionAvailable = false;
        return message;
    }

    optionAvailable = false;

    answer = -1; // prevent early answer

    nextDialogue();
    
    return message;
}
