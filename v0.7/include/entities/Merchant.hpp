#include "Npc.hpp"

// Class to handle merchant entities
class Merchant : public Npc
{
    private:
        void loadDialogue() override {
            dialogue = {
                "Welcome to my shop!",
                "We have the best goods in town.",
                "Feel free to browse around.",
                "Thank you for your patronage!"
            };
        }

    public:
        Merchant(const std::filesystem::path& textureFile, const int frameWidth, const int frameHeight, const TileMap& tileMap)
        : Npc(textureFile, frameWidth, frameHeight, tileMap) {
            loadDialogue();
        }

        void update(const Collision& collision, const sf::View& view, const sf::FloatRect& rect) { Npc::update(collision, view, rect); }
        void draw(sf::RenderWindow& window) const override { if(visible) Npc::draw(window); }
};
