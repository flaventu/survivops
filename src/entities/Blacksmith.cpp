#include "../../include/entities/Blacksmith.hpp"
using namespace std;

string Blacksmith::speak() {

    string message = dialogue[currentMessage][currentDialogueIndex++];

    if(message.substr(0,1) == ("-"))
    {
        optionAvailable = true;
        switch (answer)
        {
        case 0:
            if(player.getMoney() < findPrice()) {
                message = "You need " + to_string(findPrice() - player.getMoney()) + " more coins!";
            } else {
                message = "Great! I'll upgrade your weapon.";
                player.payMoney(findPrice());
                player.getWeapon()->upgradeWeapon();
                dialogue[currentMessage][1] = "It would cost you " + std::to_string(findPrice()) + " coins.";
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
