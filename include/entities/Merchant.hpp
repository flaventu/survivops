#include "Player.hpp"
#include "../weapons/Sword.hpp"
#include <queue>

// Class to handle merchant entities
class Merchant : public Npc
{
    private:

        // Reference to the player
        Player& player;
        std::queue<std::unique_ptr<Weapon>> inventory;

        void loadDialogue() override;

        // The price is 150 each with a discount based on the player's weapon level
        int findPrice() {
            return 150 - (player.getWeapon().getLevel()*10);
        }

    public:
    
        Merchant(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, Player& player)
        : Npc(textureFile, frameWidth, frameHeight), player(player) {
            inventory.push(std::make_unique<Sword>());
            loadDialogue();
        }

        std::string speak() override;
};
