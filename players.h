#pragma once
#include "offsets.h"
#include <vector>
#include "memory.h"
#include "character.h"
#include <memory>
#include <climits>

class Players{
    public:
        Players(const std::string &targetProcessName);
        /*
        * @param characterType 1 for enemyTeam, else for myTeam
        * @param searchType 0 for closest character, else for lowest health.
        * 
        */
        Character searchCharacter(int characterType, int searchType);
        
        Character searchCharacterByName(const std::string &name);

        std::vector<Character> getCharacters();
    protected:
        std::vector<Character> characters = {};
        std::string targetProcessName;
};