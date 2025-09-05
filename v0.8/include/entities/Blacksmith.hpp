#include "Player.hpp"

// Class to handle blacksmith entities
class Blacksmith : public Npc
{
    private:

        Player& player;

        void loadDialogue() override;

        const int findPrice() const {
            return player.getWeapon()->getLevel() * 50;
        }

    public:
    
        Blacksmith(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const TileMap& tileMap, Player& player)
        : Npc(textureFile, frameWidth, frameHeight, tileMap), player(player) {
            loadDialogue();
        }

        std::string speak() override;
};
