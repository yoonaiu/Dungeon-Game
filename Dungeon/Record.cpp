#include "Record.h"

Record::Record(){}  //open the file and clear the file


void Record::savePlayer(Player* p, ofstream& o)
{
    //player: name/tag/maxh/currenth/attack/defense/currentroomindex/preroomindex/inventory num + /n
    o<<p->getName()<<" "
    <<p->getTag()<<" "
    <<p->getMaxHealth()<<" "
    <<p->getCurrentHealth()<<" "
    <<p->getAttack()<<" "
    <<p->getDefense()<<" "
    <<p->getCurrentRoom()->getIndex()<<" "
    <<p->getPreviousRoom()->getIndex()<<" "
    <<p->getInventory().size()<<" ";//將資料輸入到檔案

    vector <Item> inventory = p->getInventory();

    for( auto x : inventory )
    {
        //item array: name/tag//health/attack/defense + /n
        o<<x.getName()<<" "
        <<x.getTag()<<" "
        <<x.getHealth()<<" "
        <<x.getAttack()<<" "
        <<x.getDefense()<<" ";
    }
}

void Record::saveRooms(vector<Room>& r, ofstream& o)
{
    // cout hm rooms first
    o<<r.size()<<" ";
    for( auto x : r ) //run the room vevtor
    {
        //index/ isExist/ uproom/ downroom/ leftroom/ rightroom / hm object + /n
        o<<x.getIndex()<<" "
        <<x.getIsExit()<<" ";

        if( x.getUpRoom() == NULL ) o<<-1<<" "; else  o<<x.getUpRoom()->getIndex()<<" ";  //**NULL的話會調用到怪怪的東西
        if( x.getDownRoom() == NULL ) o<<-1<<" "; else  o<<x.getDownRoom()->getIndex()<<" ";
        if( x.getLeftRoom() == NULL ) o<<-1<<" "; else  o<<x.getLeftRoom()->getIndex()<<" ";
        if( x.getRightRoom() == NULL ) o<<-1<<" "; else  o<<x.getRightRoom()->getIndex()<<" ";

        o<<x.getObjects().size()<<" "; //> 其實應該只會有一個 object

        vector<Object*> obj = x.getObjects();

        for( auto yy : x.getObjects() )
        {
            //need to down cast first
            if( yy->getTag() == "Item" )
            {
                Item *y = dynamic_cast<Item*>(yy);
                //tag/ name/ h/ a/ d
                o<<y->getTag()<<" "
                <<y->getName()<<" "
                <<y->getHealth()<<" "
                <<y->getAttack()<<" "
                <<y->getDefense()<<" ";
            }
            else if( yy->getTag() == "Monster" )
            {
                Monster *y = dynamic_cast<Monster*>(yy);
                //tag/ name/ mh/ ch/ a/ d
                o<<y->getTag()<<" "
                <<y->getName()<<" "
                <<y->getMaxHealth()<<" "
                <<y->getCurrentHealth()<<" "
                <<y->getAttack()<<" "
                <<y->getDefense()<<" ";
            }
            else if( yy->getTag() == "NPC" ) //NPC have object list too
            {
                NPC *y = dynamic_cast<NPC*>(yy);
                //tag/ name/ mh/ ch/ a/ d/ commodity num
                o<<yy->getTag()<<" ";

                o<<y->getCommodity().size()<<" "; // 好像只要改 r 裡面的 item vector 狀態就好
                //<<y->getScript()<<" " 先不get script
                //npc 也不用 h, a, d ...'

                vector<Item> c = y->getCommodity();
                for( auto z : c ) // all z are items
                {
                    //item array: name/tag//health/attack/defense
                    o<<z.getName()<<" "
                    <<z.getTag()<<" "
                    <<z.getHealth()<<" "
                    <<z.getAttack()<<" "
                    <<z.getDefense()<<" ";
                }
            }
            // +/n
            o<<" ";
        }
    }
}

void Record::loadPlayer(Player* p, vector<Room>& r, ifstream& i)
{
    //player: name/tag/maxh/currenth/attack/defense/currentroomindex/preroomindex/inventory num

    string n, t; //name, tag
    int mh, ch, a, d, cr, pr, innum;
    i>>n>>t>>mh>>ch>>a>>d>>cr>>pr>>innum;
    p->setName(n);
    p->setTag(t);
    p->setMaxHealth(mh);
    p->setCurrentHealth(ch);
    p->setAttack(a);
    p->setDefense(d);
    //room in player 不會有NULL的情況 (index == -1 的 situation)
    p->setCurrentRoom(&r[cr]); // room needed to be load first
    p->setPreviousRoom(&r[pr]);
    //其實可以寫 player = Player(.....) 意思同copy, 非初始化那步也可以

    for( int j = 0; j < innum; j++ )
    {
        //item array: name/tag/health/attack/defense
        string nn, tt;
        int hh, aa, dd;
        i>>nn>>tt>>hh>>aa>>dd;
        p->reloadItem( Item(nn, hh, aa, dd) );  //不用tag
        //player 的背包裏面一開始不會有任何東西，所以可以直接加載
    }
}

void Record::loadRooms(vector<Room>& r, ifstream& i)
{
    // push hm first
    // cuz start game will create all the things first, so only need to renew the information
    int hm;
    i>>hm;

    for( int j = 0; j < hm; j++ )
    {
        //index/ isExist/ uproom/ downroom/ leftroom/ rightroom / hm object + /n
        int index, isExit, uproom, downroom, leftroom, rightroom, hmo;
        i>>index>>isExit>>uproom>>downroom>>leftroom>>rightroom>>hmo;

        r[index].setIndex(index);
        r[index].setIsExit(isExit);
        if( uproom == -1 ) r[index].setUpRoom(NULL); else r[index].setUpRoom(&r[uproom]);
        if( downroom == -1 ) r[index].setDownRoom(NULL); else r[index].setDownRoom(&r[downroom]);
        if( leftroom == -1 ) r[index].setLeftRoom(NULL); else r[index].setLeftRoom(&r[leftroom]);
        if( rightroom == -1 ) r[index].setRightRoom(NULL); else r[index].setRightRoom(&r[rightroom]);


        // 把 vector 清空，如果 hmo == 0 , 直接 return , 有東西的畫 push_back 進去一個就好


        //hmo = 0;
        vector <Object*> vec; // new vec is empty
        if( hmo == 0 )
        {
            r[index].setObjects(vec);
            continue; //than return
        }

        // 每個 room 裡面都只會有一個 object 所以還好
        // tag first
        string tag;
        i>>tag; //get the tag first
        Object* p;

        if( tag == "Item" )
        {
            //name/ h/ a/ d
            string name;
            int h, a, d;
            i>>name>>h>>a>>d;
            p = new Item( name, h, a, d );
            vec.push_back(p);
            r[index].setObjects(vec);  // call the vector to push_back things
        }
        else if( tag == "Monster" )
        {
            // name/ mh/ ch/ a/ d
            string name;
            int mh, ch, a, d;
            i>>name>>mh>>ch>>a>>d;
            p = new Monster( name, mh, a, d );
            Monster *m = dynamic_cast<Monster*> (p);
            m->setCurrentHealth(ch); // need to use the set to change the things in Monster
            vec.push_back(m);
            r[index].setObjects(vec);
        }
        else if( tag == "NPC" )
        {
            // NPC 的話只需要改 r 裡面的 item vector
            vector<Item> com;
            int hmo;
            i>>hmo;
            for( int k = 0; k < hmo; k++ )
            {
                //item array: name/tag/health/attack/defense
                string name, tag;
                int h, a, d;
                i>>name>>tag>>h>>a>>d;
                com.push_back( Item(name, h, a, d) );
            }
            NPC *n = dynamic_cast<NPC*> ((r[index].getObjects())[0]);
            n->setCommodity(com);
        }
    }
}


void Record::saveToFile(Player* p, vector<Room>& r)
{
    ofstream fp;  //**fstream
    fp.open("record_player.txt", ios::out );  //open the file and 為寫入狀態, 並清空文件 | ios::trunc
    //**will open a txt in dungeon file
    savePlayer(p, fp);
    fp.close();

    ofstream fr;  //**fstream
    fr.open("record_room.txt", ios::out );
    saveRooms(r, fr);
    fr.close();
}
void Record::loadFromFile(Player* p, vector<Room>& r)
{
    ifstream fp;
    fp.open("record_player.txt", ios::in );
    loadPlayer(p, r, fp);
    fp.close();

    ifstream fr;
    fr.open("record_room.txt", ios::in );
    loadRooms(r, fr);
    fr.close();
}
