#include "../../include/entities/Merchant.hpp"
using namespace std;

string Merchant::speak() {

    dialogue[1][4] = "It costs " + std::to_string(findPrice()) + " coins.";

    if(inventory.empty()) {
        inDialogue = false;
        return "Sorry, you caught me before the restock.";
    }

    string message = dialogue[currentMessage][currentDialogueIndex++];

    if(message.substr(0,1) == ("-"))
    {
        optionAvailable = true;
        switch (answer)
        {
        case 0:
            if(player.getMoney() < 150) {
                message = "You need " + to_string(150 - player.getMoney()) + " more coins!";
            } else {
                Weapon* newWeapon = inventory.front().release();
                inventory.pop();
                message = "Great! Enjoy your new " + newWeapon->getName() + "!";
                player.payMoney(150);
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

    if(currentDialogueIndex == dialogue[currentMessage].size())
    {
        inDialogue = false;
        if(currentMessage < dialogue.size() - 1)
            currentMessage++;
    }
    return message;
}
