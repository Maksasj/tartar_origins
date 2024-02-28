#include "to_character.h"

Character* to_create_character(CombatClass combatClass) {
    Character* character = malloc(sizeof(Character));

    character->xPos = 0;
    character->yPos = 0;

    switch (combatClass) {
        case WARRIOR: {
            character->stats.stamina = 4;
            character->stats.strength = 3;
            character->stats.intellect = 1;
            character->stats.armor = 3;

            break;
        }
        case WIZARD: {
            character->stats.stamina = 3;
            character->stats.strength = 1;
            character->stats.intellect = 3;
            character->stats.armor = 1;

            break;
        }
    }

    return character;
}
