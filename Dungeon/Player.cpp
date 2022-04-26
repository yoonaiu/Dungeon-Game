#include "Player.h"


Player::Player():GameCharacter() {}

Player::Player(string name, int maxHealth, int attack, int defense)
:GameCharacter(name, "Player", maxHealth, attack, defense) {}

void Player::addItem(Item i) //**add item into the vector
{
    this->inventory.push_back(i);
    increaseStates(i.getHealth(), i.getAttack(), i.getDefense());
};
void Player::reloadItem(Item i)
{
    this->inventory.push_back(i);
}

void Player::increaseStates(int hp,int ap,int dp)  //**升級嗎~
{
    //不能用this去access父類別的private member
    //***基類的private member只能被基類的友元函式或基類的成員函式access
    //用GC的member function 去 reset 值
    setMaxHealth(this->getMaxHealth()+hp);
    setCurrentHealth(this->getCurrentHealth()+hp);
    setAttack(this->getAttack()+ap);
    setDefense(this->getDefense()+dp);
};
void Player::changeRoom(Room* newRoom)
{
    mciSendString(TEXT("open step.mp3 alias step"), NULL, 0, NULL);
    mciSendString(TEXT("play step repeat"), NULL, 0, NULL);
    Sleep(1500);
    mciSendString(TEXT("close step"), NULL, 0, NULL);//关闭报警音 */
    this->previousRoom = this->currentRoom;
    this->currentRoom = newRoom;
    cout<<"Now you are in Room"<<(this->getCurrentRoom()->getIndex())<<endl;
};

bool Player::triggerEvent( Object* pp )
{
    /*mciSendString(TEXT("open bling.mp3 alias bling"), NULL, 0, NULL);
    mciSendString(TEXT("play bling repeat"), NULL, 0, NULL);
    Sleep(1000);
    mciSendString(TEXT("close bling"), NULL, 0, NULL);*/

    Player *p = dynamic_cast<Player *> (pp);
    cout<<"["<<this->getName()<<"]"<<endl  //[Player's name]
    <<"> Health: "<<this->getCurrentHealth()<<"/"<<this->getMaxHealth()<<endl  //> Health: 100/100
    <<"> Attack: "<<this->getAttack()<<endl  //> Attack: 30
    <<"> Defense: "<<this->getDefense()<<endl;  //> Defense: 0

    return true;
}


void Player::setCurrentRoom(Room* currentRoom)
{
    this->currentRoom = currentRoom;
};
void Player::setPreviousRoom(Room* previousRoom)
{
    this->previousRoom = previousRoom;
};
void Player::setInventory(vector<Item> inventory)
{
    this->inventory = inventory;
};


Room* Player::getCurrentRoom()
{
    return this->currentRoom;
};
Room* Player::getPreviousRoom()
{
    return this->previousRoom;
};
vector<Item> Player::getInventory()
{
    return this->inventory;
};
