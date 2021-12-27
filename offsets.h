//works for 11.24

//https://www.unknowncheats.me/forum/3314071-post5351.html
//To calculate in future we can also use IDA and LeagueDumper
//https://www.unknowncheats.me/forum/league-of-legends/320116-dump-lol-addresses-guide.html

#pragma once

#define playerOffset 0x3109D4C
#define myTeamOffset 0x3100
#define eachCharacterOffset 0x1c0
#define enemyTeamOffset myTeamOffset + 4*eachCharacterOffset
#define healthOffset 0xDB4
#define maxHealthOffset healthOffset + 0x10
#define manaOffset 0x2B4
#define maxManaOffset manaOffset+0x10
#define heroNameOffset 0x2DA4
#define gameTimeOffset 0x3101314
#define characterLevelOffset 0x3394
#define characterPositionOffset 0x1F4
#define characterBaseAttackOffset 0x12BC
#define characterBonusAttackOffset 0x1234
#define characterAbilityPowerOffset 0x1788
#define characterMovSpeedOffset 0x12FC
#define characterTotalArmour 0x12E4 
#define characterBonusArmour characterTotalArmour + 0x4
#define teamOffset 0x4C 

#define spellBookOffset 0x2370
#define spellSlotOffset 0x488
#define spellInfoOffset 0x13C

#define spellLevelIOffset 0x20 
#define spellDataOffset 0x18