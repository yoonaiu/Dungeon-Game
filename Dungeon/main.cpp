#include <iostream>
#include <string>
#include <vector>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"


using namespace std;

int main(){
    Dungeon dungeon = Dungeon();
    dungeon.runDungeon();  // run 了以後再create 東西好了
    return 0;
}
