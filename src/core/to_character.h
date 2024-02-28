#ifndef _TO_CORE_CHARACTER_H_
#define _TO_CORE_CHARACTER_H_

#include <stdlib.h>

typedef long long statType;

typedef struct StatBlock {
    statType stamina;
    statType strength;
    statType intellect;
    statType armor;
} StatBlock;

typedef struct Character {
    StatBlock stats;

    int xPos;
    int yPos;
} Character;

typedef enum CombatClass {
    WARRIOR,
    WIZARD
} CombatClass;

Character* to_create_character(CombatClass combatClass);

#endif