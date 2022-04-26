#include "Monster.h"
//#include "Player.h"  //down casting 那邊要用到


Monster::Monster():GameCharacter() {}  //***不可多重繼承都寫在這!好像一次只能寫一層!!

Monster::Monster(string name, int maxHealth, int attack, int defense)
:GameCharacter(name, "Monster", maxHealth, attack, defense)  {}
//, Object(name, "Monster"): {}  //****多層繼承建構子寫法



bool Monster::triggerEvent( Object* pp )  //combat system included
{
    Player *p = dynamic_cast<Player *> (pp);

    cout<<"cuz there is a monster room, you can only choose: \n"<<endl
    <<"A. stay and fight the monster"<<endl
    <<"B. retreat to the previous room"<<endl
    <<"貼心小提醒: 沒打敗怪物不能前進喔 ^^"<<endl;

    char di;
    cin>>di;
    cout<<"\n\n";
    char dii;

    if( di == 'A' )
    {
        //list the information of the monster first
        cout<<"Monster "<<"["<<this->getName()<<"]"<<endl  //[Monster's name]
        <<"> Health: "<<this->getCurrentHealth()<<"/"<<this->getMaxHealth()<<endl  //> Health: 100/100
        <<"> Attack: "<<this->getAttack()<<endl  //> Attack: 30
        <<"> Defense: "<<this->getDefense()<<endl;

        mciSendString(TEXT("open mons.mp3 alias mons"), NULL, 0, NULL);
        mciSendString(TEXT("play mons repeat"), NULL, 0, NULL);
        Sleep(2900);
        mciSendString(TEXT("close mons"), NULL, 0, NULL);

        cout<<"\nplease enter an arbitrary letter to continue\n";
        cin>>dii;

        while(1)
        {
            mciSendString(TEXT("open sword.mp3 alias sword"), NULL, 0, NULL);
            mciSendString(TEXT("play sword repeat"), NULL, 0, NULL);
            Sleep(2000);
            mciSendString(TEXT("close sword"), NULL, 0, NULL);
            //player attack first
            this->takeDamage( p->getAttack() - this->getDefense() ); //p's attack - m's defense
            cout<<"You hit Monster "<<this->getName()<<" for "<<p->getAttack()<<"points!"<<endl;
            if( this->checkIsDead() )
                break;

            //monster attack next
            p->takeDamage( this->getAttack() - p->getDefense() );  //m's attack - p's defense
            cout<<"Monster "<<this->getName()<<" hit you for "<<this->getAttack()<<"points!"<<endl;
            if( p->checkIsDead() )
                break;

            while(1)
            {
                int bol = attack_retreat();
                if( bol == 1 )
                    break;
                else if( bol == 0 )  //retreat
                {
                    p->changeRoom( p->getPreviousRoom() );
                    return true; //handle 完就 retreat
                }
                else
                {
                    cout<<"enter invalid!\n";  //continue
                }
            }
        }
    }
    else if( di == 'B' )
    {
        p->changeRoom( p->getPreviousRoom() );  // handle retreat in monster
    }

    return true;
}


int attack_retreat()
{
    cout<<"\nChoose next action:\n"
    <<"A. Attack!\n"
    <<"B. Retreat!\n";
    char dii;
    cin>>dii;

    if( dii == 'A' )
        return 1; //1 means continue
    else if( dii == 'B' )
        return 0; //0 means retreat
    else
        return 2;  //invalid input

}
