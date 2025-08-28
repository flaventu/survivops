#include "../const.hpp"

class Weapon {

    private:

        // Texture
        const sf::Texture textureSheet;
        sf::Sprite weaponSprite;

        // Attributes
        int level = 1;
        int maxLevel = 5;

        bool usable = true;

    protected:

        // Stats
        int damage;
        int range;
        int cooldown; // milliseconds
        sf::Clock cooldownClock;

        virtual void updateStats() = 0;

    public:

        Weapon(const std::filesystem::path& textureFile, const int dmg, const int rng, const int cd) 
            : textureSheet(textureFile), weaponSprite(textureSheet), damage(dmg), range(rng), cooldown(cd), cooldownClock() 
            {  
                weaponSprite.setTextureRect(sf::IntRect({TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE}));
                weaponSprite.setOrigin({TILE_SIZE / 2, TILE_SIZE / 2});
                weaponSprite.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 80.f});
            }
        
        // Getters
        const int getDamage() const { return damage; }
        const int getRange() const { return range; }
        const int getLevel() const { return level; }
        bool isUsable() const { return usable; }

        void useWeapon();

        void upgradeWeapon() {
            if(level < maxLevel) {
                level++;
                updateStats();
                weaponSprite.setTextureRect(sf::IntRect({TILE_SIZE, (level - 1) * static_cast<int>(TILE_SIZE)}, {TILE_SIZE, TILE_SIZE}));
            }
        }

        void update();
        void draw(sf::RenderWindow& window) const { window.draw(weaponSprite); }
};