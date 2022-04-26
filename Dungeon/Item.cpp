#include "Item.h"

Item::Item():Object() { }  //**nothing, if there is name passed in, it must have other attribute to be passed in, will not use this default
//sth wrong cuz the virtual function not yet implement

Item::Item(string name, int health, int attack, int defense)
:Object(name, "Item")  //**name can be passed in by derived constructor's parameter, tag is "Item"
{
    this->health = health;
    this->attack = attack;
    this->defense = defense;
}
//constructor 沒有返回值


void Item::setHealth(int health)
{
    this->health = health;
}
void Item::setAttack(int attack)
{
    this->attack = attack;
}
void Item::setDefense(int defense)
{
    this->defense = defense;
}


int Item::getHealth()
{
    return this->health;
}
int Item::getAttack()
{
    return this->attack;
}
int Item::getDefense()
{
    return this->defense;
}


bool Item::triggerEvent( Object* pp )  //return true if pickup
{
    //if its item's trigger event : increase status
    Player *p = dynamic_cast<Player *> (pp);  //** all the passing type is pointer: 方便操作

    if( this->getName() == "Chest" )
    {
        cout<<"Open it?"<<endl;
    }
    else
    {
        cout<<"Pick up this item?"<<endl;
    }
    cout<<"A. Yes"<<endl
    <<"B. No"<<endl;

    char di;
    cin>>di;
    cout<<"\n";

    if( di == 'A' )  //after pick up the item, the item needed to be "erase" from the room or the NPC
    {
        if( this->getName() == "Chest" )
        {
            mciSendString(TEXT("open chest.mp3 alias chest"), NULL, 0, NULL);
            mciSendString(TEXT("play chest repeat"), NULL, 0, NULL);
            Sleep(1000);
            mciSendString(TEXT("close chest"), NULL, 0, NULL);

            mciSendString(TEXT("open coin.mp3 alias coin"), NULL, 0, NULL);
            mciSendString(TEXT("play coin repeat"), NULL, 0, NULL);
            Sleep(1000);
            mciSendString(TEXT("close coin"), NULL, 0, NULL);

            cout<<"You have opened the chest, and";
            p->addItem( (*this) );  //**
            p->getCurrentRoom()->eraseObject(0);
        }
        else
        {
            cout<<"Item "<<this->getName()<<" is added to the backpack, and";
            p->addItem( (*this) );  //**
        }
        cout<<" your status is updated: "<<endl;
        p->triggerEvent(p);  //show the player's status
    }
    else
    {
        cout<<"enter invalid\n";
        return true;
    }

    return true;  // successfully equiped or actually not
}

//**程式層級的operator overloading for cout<<Item
ostream& operator<<(ostream& out, Item& k) //const for 不希望改到值, reference for 不需要copy
{
    string name;
    name = k.getName(); //get name is the public function 2 layers before
    int health, attack, defense;
    health = k.getHealth();  //**k: just like the object itself, can be used as the obj
    attack = k.getAttack();
    defense = k.getDefense();

    out<<"name: "<<name<<"\n"<<"hp: "<<health<<"\n"<<"attack: "<<attack<<"\n"<<"defense: "<<defense<<"\n\n";
    return out;
}



