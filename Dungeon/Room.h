#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Room  //�S���~�� object!!~
{
private:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
    bool isExit;
    int index;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
                             //�ƦX���Y: Room����object���w
public:
    Room();
    Room(bool, int, vector<Object*>);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/

    /* Set & Get function*/
    void setUpRoom(Room*);  // catch ���ܼƫ��A�A�ҥH�ǹL�Ӫ��n�O reference &
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object*>);
    void eraseObject(int);  // pass in the index of the element in this array to erase the specified object
    bool getIsExit();
    int getIndex();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
};

#endif // ROOM_H_INCLUDED
