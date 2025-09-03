#include "../../include/entities/Merchant.hpp"
using namespace std;

void Merchant::loadDialogue() {
    dialogue = {
        {
            "Looking for deals?",
            "I have the best weapons in town.",
            "Come and visit me anytime!"
        },
        {
            "Seems like you need a weapon.",
            "Mh... let me see...",
            "Here you go!",
            "I have this " + inventory.front()->getName() + " for sale.",
            "It costs ... coins.",
            "What do you think?",
            "- I'll take it!\n- No thanks."
        }
    };
}

string Merchant::speak() {

    // Update the dialogue with the current price
    dialogue[1][4] = "It costs " + std::to_string(findPrice()) + " coins.";

    // Check if the inventory is empty
    if(inventory.empty()) {
        inDialogue = false;
        return "Sorry, you caught me before the restock.";
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

            // Shop logic
            if(player.getMoney() < findPrice()) {
                message = "You need " + to_string(findPrice() - player.getMoney()) + " more coins!";
            } else {
                Weapon* newWeapon = inventory.front().release();
                inventory.pop();
                message = "Great! Enjoy your new " + newWeapon->getName() + "!";
                player.payMoney(findPrice());
                player.changeWeapon(std::unique_ptr<Weapon>(newWeapon));
                if(!inventory.empty())
                    dialogue[currentMessage][3] = "I have this " + inventory.front()->getName() + " for sale.";
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
