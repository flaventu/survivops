#pragma once
#include "Npc.hpp"
#include "../weapons/Hand.hpp"

// Class to handle the player character
class Player : public Entity
{
    private:

        // Attributes
        int level = 1;
        float dodge = 5.f; // %

        int money = 0;
        float expForNew = level * 100;
        float currentExp = 0;

        Weapon* weapon;

        std::vector<std::unique_ptr<Weapon>> inventory;
        int currentWeaponIndex = 1;

    public:

        Player() : Entity("assets/entities/player/spritesheet.png", TILE_SIZE, TILE_SIZE)
        { 
            position = {0, 0}; 
            speed = 3;
            totalHealth = 20.f;
            currentHealth = totalHealth;
            inventory.push_back(std::make_unique<Hand>());
            weapon = inventory.back().get();
        }

        // Dialogue
        bool dialogueActive = false;
        Entity* currentNpc = nullptr;

        // Combat
        bool isAttacking = false;
        bool attack(const Collision&, const std::vector<std::shared_ptr<Entity>>&);
        const float getDodge() const { return dodge; };

        // Getters
        const float getHealth() const { return currentHealth; };
        const int getMoney() const { return money; };
        Weapon& getWeapon() const { return *weapon; };
        
        // Setters
        void gainMoney(const int coins) { money += coins; };
        void payMoney(const int coins) { money -= coins; };
        void gainExp(const float);
        void changeWeapon() { weapon = inventory[currentWeaponIndex++ % inventory.size()].get(); }
        void addWeapon(std::unique_ptr<Weapon> newWeapon) { inventory.push_back(std::move(newWeapon)); }

        // Player state
        void upgradePlayer();
        void respawn() { currentHealth = totalHealth; money = 0; entitySprite.setColor(sf::Color::White); };

        // UI utils
        const int getCurrentLevel() const { return level; };
        const float getExpPerc() const { return currentExp/expForNew; };

        void update(const DIRECTIONS, const Collision&, const std::vector<std::shared_ptr<Entity>>&);
};
