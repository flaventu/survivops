#include "Player.hpp"
#include "../weapons/Sword.hpp"
#include <queue>

// Class to handle merchant entities
class Merchant : public Npc
{
    private:

        Player& player;
        std::queue<std::unique_ptr<Weapon>> inventory;

        void loadDialogue() override;

        int findPrice() {
            return 150 - (player.getWeapon()->getLevel()*10);
        }

    public:
        Merchant(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const TileMap& tileMap, Player& player)
        : Npc(textureFile, frameWidth, frameHeight, tileMap), player(player) {
            inventory.push(std::make_unique<Sword>());
            loadDialogue();
        }

        std::string speak() override;
};
