#pragma once
#include "Npc.hpp"
#include "../weapons/Hand.hpp"

// Class to handle the player character
class Player : public Entity
{
    private:

        // Attributes
        int level = 1;
        float power = 5.f;
        float dodge = 5.f; // %

        int money = 0;
        float expForNew = level * 100;
        float currentExp = 0;

        // Animation
        sf::Clock animationClock;
        void animate() override;

        std::unique_ptr<Weapon> weapon;

    public:

        Player() : Entity("assets/entities/player/spritesheet.png", TILE_SIZE, TILE_SIZE), animationClock(), weapon(std::make_unique<Hand>())
        { 
            position = {0, 0}; 
            speed = 3;
            totalHealth = 20.f;
            currentHealth = totalHealth;
        }

        // Dialogue
        bool dialogueActive = false;
        Entity* currentNpc = nullptr;

        // Combat
        bool isAttacking = false;
        bool attack(const Collision&, const std::vector<std::shared_ptr<Entity>>&);

        // Getters
        const float getHealth() const { return currentHealth; };
        const int getMoney() const { return money; };
        Weapon& getWeapon() const { return *weapon.get(); };
        
        // Setters
        void gainMoney(const int coins) { money += coins; };
        void payMoney(const int coins) { money -= coins; };
        void gainExp(const float);
        void changeWeapon(std::unique_ptr<Weapon> newWeapon) { weapon = std::move(newWeapon); }

        // Player state
        void upgradePlayer();
        void respawn() { currentHealth = totalHealth; position = {0, 0}; };
        
        // UI utils
        const int getCurrentLevel() const { return level; };
        const float getExpPerc() const { return currentExp/expForNew; };

        void update(const DIRECTIONS, const Collision&, const std::vector<std::shared_ptr<Entity>>&);
};
