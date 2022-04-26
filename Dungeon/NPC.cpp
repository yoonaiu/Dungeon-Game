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
    //**���M��vector : 1. �^�N��(�{�b�S�H�b�ΤF)  2. vector���}�C��0~size-1�h�M��  3.  auto x
    /* sol 2
    for( int i = 0; i < (commodity.size); i++ )  *commodity.size
        cout<<commodity[i]<<endl;                 �N�O�{�b�o��vector�̭�����F�h�֪F�誺�N��(vector ����function)
                                                  "���ovector�ثe�����������Ӽ�"
    */
    //sol3: auto x

    int i = 0;
    for( auto x:this->commodity )  //�bcommodity �����C�Ӥ���, �O�o��NPC::...���M�|��this in nonmember function����
    {
        cout<<"\n"<<i<<".\n"<<x; //�ιB��ŭ�����{
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

    this->commodity.erase(commodity.begin() + n);  //**�R���}�C���Y����
}

