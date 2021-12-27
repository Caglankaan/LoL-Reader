#include "character.h"
#include <iostream>
#include "Vector.h"
Character::Character(std::string targetProcessName, int characterType, int charCount) : 
                targetProcessName(targetProcessName),
                characterType(characterType)
            {
            mem.GetDebugPrivileges();
            
            int processId = mem.GetProcessId(targetProcessName.c_str());
            processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
            baseAddr = mem.GetModuleBase(processHandle, targetProcessName);
            if(characterType == 0)
                playerAddr = mem.ReadInt(processHandle, baseAddr + playerOffset);
            else if(characterType == 1)
                playerAddr = mem.ReadInt(processHandle, baseAddr + playerOffset+myTeamOffset+charCount*eachCharacterOffset);
            else
                playerAddr = mem.ReadInt(processHandle, baseAddr + playerOffset+enemyTeamOffset+charCount*eachCharacterOffset);

        }

float Character::getHealth(){
    return mem.ReadFloat(processHandle, playerAddr + healthOffset);
}

float Character::getMaxHealth(){
    return mem.ReadFloat(processHandle, playerAddr + maxHealthOffset);
}

float Character::getMana(){
    return mem.ReadFloat(processHandle, playerAddr + manaOffset);
}

float Character::getMaxMana(){
    return mem.ReadFloat(processHandle, playerAddr + maxManaOffset);
}

float Character::getBaseAttack(){
    return mem.ReadFloat(processHandle, playerAddr + characterBaseAttackOffset);
}

float Character::getBonusAttack(){
    return mem.ReadFloat(processHandle, playerAddr + characterBonusAttackOffset);
}

float Character::getAbilityPower(){
    return mem.ReadFloat(processHandle, playerAddr + characterAbilityPowerOffset);
}

float Character::getGameTime(){
    return mem.ReadFloat(processHandle, baseAddr + gameTimeOffset);
}

float Character::getMovementSpeed(){
    return mem.ReadFloat(processHandle, playerAddr + characterMovSpeedOffset);
}

float Character::getTotalArmour(){
    return mem.ReadFloat(processHandle, playerAddr + characterTotalArmour);
}

float Character::getBonusArmour(){
    return mem.ReadFloat(processHandle, playerAddr + characterBonusArmour);
}

int Character::getCharacterLevel(){
    return mem.ReadInt(processHandle, playerAddr + characterLevelOffset);
}

std::string Character::getHeroName(){
    return mem.ReadText(processHandle, playerAddr + heroNameOffset);
}

Vector3 Character::getPosition(){
    Vector3 vec = mem.ReadVector(processHandle, playerAddr+characterPositionOffset);
    return vec;
    std::cout << "Position x: " << vec.x <<" y: " << vec.y  << " z: " << vec.z << "\n";
}

