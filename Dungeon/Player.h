#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

#include<Windows.h>
#include<mmsystem.h>
#include<dsound.h>
#pragma comment(lib,"WINMM.LIB")

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;  //the Room here is pointer!!~~ to point the real room in the room vector, so can use the info in the real room
    Room* previousRoom;
    vector<Item> inventory;
public:
    Player();
    Player(string,int,int,int);  //name, mhealth, attack, defense
    void addItem(Item);
    void reloadItem(Item); //**
    void increaseStates(int,int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item> getInventory();
};

#endif // PLAYER_H_INCLUDED
