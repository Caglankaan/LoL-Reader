#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "character.h"
#include "players.h"
#include <limits>

void cls()
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    std::cout.flush();

    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
    
    DWORD written;

    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    SetConsoleCursorPosition(hOut, topLeft);
}

void updateStatus(Character character){
    std::cout << "\tCurrent Game Time :\t" << int(character.getGameTime()/60) <<":"<<int(character.getGameTime())%60<< "\n";
    std::cout << "\tCurrent health: \t" << character.getHealth() << "\n";
    std::cout << "\tMax health: \t\t" << character.getMaxHealth() << "\n";
    std::cout << "\tCurrent mana: \t\t" << character.getMana() << "\n";
    std::cout << "\tMax mana: \t\t" << character.getMaxMana() << "\n";
    std::cout << "\tBase attack: \t\t" << character.getBaseAttack() << "\n";
    std::cout << "\tBonus attack: \t\t" << character.getBonusAttack() << "\n";
    std::cout << "\tAbility power: \t\t" << character.getAbilityPower() << "\n";
    std::cout << "\tMovement speed: \t" << character.getMovementSpeed() << "\n";
    std::cout << "\tTotal armour: \t\t" << character.getTotalArmour() << "\n";
    std::cout << "\tBonus armour: \t\t " << character.getBonusArmour() << "\n";
    std::cout << "\tHero name: \t\t" << character.getHeroName() << "\n";
    std::cout << "\tHero level: \t\t" << character.getCharacterLevel() << "\n";
    Vector3 vec = character.getPosition();
    std::cout << "\tPosition x: " << vec.x <<" y: " << vec.y  << " z: " << vec.z << "\n";


    character.getPosition();
}

void loop(Players players){
    int x;
    std::cout << "Enter number:\n\t1 - Get your characters status.\n";
    std::cout << "\t2 - Get all your teams status.\n";
    std::cout << "\t3 - Get all enemy teams status.\n";
    std::cout << "\t4 - Get closest enemy stats.\n";
    std::cout << "\t5 - Get closest team member stats.\n";
    std::cout << "\t-1 - Quit\n";
    while(true){
        while (!(std::cin >> x)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a number: ";
        }
        cls();
        if(x == -1){
            std::cout <<"Bye\n";
            exit(1);
        }
        else if(x == 1){
            updateStatus(players.getCharacters()[0]);
        }
        else if(x == 2){
            for(int i = 0; i < 5; i++){
                std::cout << std::to_string(i+1) << ". player: \n";
                updateStatus(players.getCharacters()[i]);
            }
        }
        else if(x == 3){
            for(int i = 5; i < 10; i++){
                std::cout << std::to_string(i+1) << ". player: \n";
                updateStatus(players.getCharacters()[i]);
            }
        }
        else if(x == 4){
            std::cout << "Closest enemy stats: \n";
            updateStatus(players.searchCharacter(1,0));
        }
        
        else if(x == 5){
            std::cout << "Closest teammate stats: \n";
            updateStatus(players.searchCharacter(0,0));
        }
        std::cout << "What next(1-5): ";
    }
}

int main()
{
    
    std::string TARGET_PROCESS_NAME = "League of Legends.exe";
    Players players{TARGET_PROCESS_NAME};
    loop(players);
    
    return 0;
}