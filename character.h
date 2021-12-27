#pragma once
#include "offsets.h"
#include <vector>
#include "memory.h"

class Character{
    public:
    //character type: 0-> me, 1->friend, 2->enemy
    Character(std::string targetProcessName, int characterType, int charCount);
        float getHealth();
        float getMaxHealth();
        float getMana();
        float getMaxMana();
        float getBaseAttack();
        float getBonusAttack();
        float getAbilityPower();
        float getGameTime();
        float getMovementSpeed();
        float getTotalArmour();
        float getBonusArmour();

        int getCharacterLevel();
        std::string getHeroName();

        Vector3 getPosition();

    protected:
        HANDLE processHandle;
        std::string targetProcessName;
        int playerAddr;
        int baseAddr;
        Memory mem;
        int characterType;
        
};