#include "players.h"

Players::Players(const std::string &targetProcessName) : 
    targetProcessName(targetProcessName) {
        for(int i = 0; i < 10; i ++){
            if(i >= 1 && i <=4)//myteam
                characters.emplace_back(Character(targetProcessName, 1, i-1));
            else if(i==0)//local character
                characters.emplace_back(Character(targetProcessName, 0, 0));
            else //enemy
                characters.emplace_back(Character(targetProcessName, 2, i-5));
        }
    }

Character Players::searchCharacter(int characterType, int searchType){
    int index = -1;
    int minIndex = INT_MAX;
    if(searchType == 0){
        Vector3 currentPos = characters[0].getPosition();
        if(characterType == 1){
            for(int i = 5; i < 10; i++){
                int dst = currentPos.distance(characters[i].getPosition());
                if(dst < minIndex){
                    minIndex = dst;
                    index = i;
                }
            }
        }
        else{
            for(int i = 1; i < 5; i++){
                int dst = currentPos.distance(characters[i].getPosition());
                if(dst < minIndex){
                    minIndex = dst;
                    index = i;
                }
            }
        }
    }
    if(index != -1)
        return characters[index];
}

Character Players::searchCharacterByName(const std::string &name){
    for(int i = 0; i < 10; i++){
        if(characters[i].getHeroName() == name)
            return characters[i];
    }
}

std::vector<Character> Players::getCharacters(){
    return characters;
}