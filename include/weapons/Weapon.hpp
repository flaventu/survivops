#pragma once
#include "../const.hpp"

class Weapon {

    private:

        std::string name;

        // Texture
        const sf::Texture textureSheet;
        sf::Sprite weaponSprite;

        // Attributes
        int level = 1;
        int maxLevel = 5;

        bool usable = true;

    protected:

        // Stats
        float damage;
        float range;
        float cooldown; // milliseconds
        sf::Clock cooldownClock;

        virtual void updateStats() = 0;

    public:

        Weapon(const std::filesystem::path& textureFile, const std::string nm, float dmg, float rng, float cd) 
            : name(nm), textureSheet(textureFile), weaponSprite(textureSheet), damage(dmg), range(rng), cooldown(cd), cooldownClock() 
            {  
                weaponSprite.setTextureRect(sf::IntRect({TILE_SIZE, 0}, {TILE_SIZE, TILE_SIZE}));
                weaponSprite.setOrigin({TILE_SIZE / 2, TILE_SIZE / 2});
                weaponSprite.setPosition({SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 80.f});
            }

        virtual ~Weapon() = default;
        
        // Getters
        const std::string& getName() const { return name; }
        float getDamage() const { return damage; }
        float getRange() const { return range; }
        int getLevel() const { return level; }
        int getMaxLevel() const { return maxLevel; }
        bool isUsable() const { return usable; }

        void useWeapon();

        // Update stats and appearance
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