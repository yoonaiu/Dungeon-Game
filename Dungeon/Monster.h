#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;

class Monster: public GameCharacter
{
private:
public:
    Monster();
    Monster(string,int,int,int); //name(1: object), maxh, attack, defense(2: Gcharacter)

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*);
};

int attack_retreat(); //new function need to declare here

#endif // ENEMY_H_INCLUDED
