#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Item: public Object   //Ä~©Ófrom Object
{
private:
    int health,attack,defense;
public:
    Item();
    Item(string, int, int, int); //name, mh, a, d

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
    int getHealth();
    int getAttack();
    int getDefense();
};

ostream& operator<<(ostream&, Item&); //needed to declare this function in header file first!!->or will be wrong

#endif // ITEM_H_INCLUDED
