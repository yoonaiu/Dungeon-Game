#include "NPC.h"

NPC::NPC():GameCharacter() {}

NPC::NPC(string name, string script, vector<Item> commodity):
GameCharacter(name, "NPC", 100, 0, 0) //max health:100, attack, defense:0
{
    this->script = script;
    this->commodity = commodity;
}


void NPC::listCommodity()  //list all the Items in this NPC
{
    //**怎麼遍歷vector : 1. 跌代器(現在沒人在用了)  2. vector當成陣列用0~size-1去遍歷  3.  auto x
    /* sol 2
    for( int i = 0; i < (commodity.size); i++ )  *commodity.size
        cout<<commodity[i]<<endl;                 就是現在這個vector裡面有放了多少東西的意思(vector 內部function)
                                                  "取得vector目前持有的元素個數"
    */
    //sol3: auto x

    int i = 0;
    for( auto x:this->commodity )  //在commodity 內的每個元素, 記得打NPC::...不然會報this in nonmember function的錯
    {
        cout<<"\n"<<i<<".\n"<<x; //用運算符重載實現
        i++;
    }
}


void NPC::setScript(string script)
{
    this->script = script;
}
void NPC::setCommodity(vector<Item> commodity)
{
    this->commodity = commodity;
}

string NPC::getScript()
{
    return this->script;
}
vector<Item> NPC::getCommodity()
{
    return this->commodity;
}



bool NPC::triggerEvent( Object* pp )
{
    Player *p = dynamic_cast<Player *> (pp);

    mciSendString(TEXT("open old.mp3 alias old"), NULL, 0, NULL);
    mciSendString(TEXT("play old repeat"), NULL, 0, NULL);
    Sleep(2000);
    mciSendString(TEXT("close old"), NULL, 0, NULL);

    cout<<getScript();
    if(this->commodity.empty())
    {
        cout<<"\nI don't have any item now~ QQ\n";
        return true;
    }

    this->listCommodity();

    cout<<"Please enter the number of the commodity you would like to buy:\n";
    int n; cin>>n;
    cout<<"\n"; //**not sure here
    if( n >= this->commodity.size() )
    {
        cout<<"\n"<<"enter invalid\n";
        return true;
    }

    cout<<"Item "<<this->commodity[n].getName()<<" is added to the backpack, and";
    p->addItem(this->commodity[n]);  //**
    cout<<" your status is updated: \n"<<endl;
    p->triggerEvent(p);  //show the player's status

    this->commodity.erase(commodity.begin() + n);  //**刪除陣列中某元素
}

