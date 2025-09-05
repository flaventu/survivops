#include "Player.hpp"

// Class to handle blacksmith entities
class Blacksmith : public Npc
{
    private:

        // Reference to the player
        Player& player;

        void loadDialogue() override;

        // The price is based on the player's weapon level
        const int findPrice() const {
            return player.getWeapon().getLevel() * 50;
        }

    public:

        Blacksmith(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, Player& player)
        : Npc(textureFile, frameWidth, frameHeight), player(player) {
            loadDialogue();
        }

        std::string speak() override;
};
