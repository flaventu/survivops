#include "Npc.hpp"

// Class to handle merchant entities
class Merchant : public Npc
{
    private:
        void loadDialogue() override {
            dialogue = {
                {
                    "Looking for deals?",
                    "I have the best weapons in town.",
                    "Come and visit me anytime!"
                },
                {
                    "Sorry...",
                    "you caught me before the restock."
                }
            };
        }

    public:
        Merchant(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const TileMap& tileMap)
        : Npc(textureFile, frameWidth, frameHeight, tileMap) {
            loadDialogue();
        }
};
