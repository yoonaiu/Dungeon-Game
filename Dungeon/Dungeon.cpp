#include "Dungeon.h"

/* Create a new player, and give him/her basic status */
Dungeon::Dungeon() {}

void Dungeon::startGame()
{
    cout<<"Do you want to continue the previous game or restart?\n"
    <<"A. continue\n"
    <<"B. restart\n";

    char di;
    cin>>di;

    createPlayer();  // here will ask the name, avoid to call the quote twice, write here after input
    createMap();

    if( di == 'A' )
    {
        //no need default constructor!!~~ player & room is already make in the .h file
        Record r;
        r.loadFromFile(&player, rooms);
    }
    else if( di == 'B' )
    {
        string name;
        cout<<"Now, you need to get a new character in this game~"<<endl
        <<"Please enter the name you want for this character first:";
        cin>>name;
        player.setName(name);
        return;
        // directly return, 不用複寫
    }
    else
    {
        cout<<"\nenter invalid\n";
        startGame();  // call itself again
        return; //avoid print the room info string twice
    }


    cout<<"\nNow you are in Room "<<player.getCurrentRoom()->getIndex()<<"\n\n";
}


void Dungeon::createPlayer()
{
    int maxHealth, attack, defense;
    /*
    cout<<"name: "; cin>>name;
    cout<<"maxHealth: "; cin>>maxHealth;
    cout<<"attack: "; cin>>attack;
    cout<<"defense: "; cin>>defense;
    */
    player = Player(" ", 20, 5, 5);  // use constructor(public) from Player to initialize Dungeon's member: player
}


/* Create a map, which include several different rooms */
void Dungeon::createMap()  //先寫死，目前不需要玩家輸入的部分
{
    //need to creat object and push into a object vector first
    //rooms is a vector which store room variable


    // Room[0] : start room, nothing in here
    vector<Object*> obj0;
    rooms.push_back(Room(false, 0, obj0));



    // Room[1] : 催狂魔 there is a monster, so create a object vector
    Object* p1;
    p1 = new Monster("Dementor__催狂魔", 10, 10, 0);  // 因為Monster constructor
    vector<Object*> obj1;                   // constructor 在使用完後就會消失了，所以要用new直接開出一塊內存給 pointer 指
    obj1.push_back(p1);
    rooms.push_back(Room(false, 1, obj1));



    //Room[2] : there is a chest
    Object* p2;
    p2 = new Item("Chest", 10, 0, 0);
    vector<Object*> obj2;
    obj2.push_back(p2);
    rooms.push_back(Room(false, 2, obj2));



    //Room[3] : Death Eater  食死人
    Object* p3;
    p3 = new Monster("Death_Eater__食死人", 20, 10, 0);  // 因為Monster constructor
    vector<Object*> obj3;                   // constructor 在使用完後就會消失了，所以要用new直接開出一塊內存給 pointer 指
    obj3.push_back(p3);
    rooms.push_back(Room(false, 3, obj3));


    //Room[4] :NPC 鄧不力多 there is a NPC(seller), and the NPC has a item: cherry blossom
    // 1. 奶啤,  2. 魔杖  3. 隱形斗篷
    vector<Item> NPC_item_v;

    //Item *butterbeer;
    //butterbeer = new Item("Butterbeer", 180, 0, 0); //mh, a, d
    NPC_item_v.push_back(Item("Butterbeer", 120, 0, 0));  //can pushback the constructor

    //Item *magicwand;
    //magicwand = new Item("Magic wand", 0, 25, 0);
    NPC_item_v.push_back(Item("Magic_wand", 0, 35, 0));

    //Item *InvisibilityCloak;
    //InvisibilityCloak = new Item("Invisibility Cloak", 0, 0, 10);
    NPC_item_v.push_back(Item("Invisibility_Cloak", 0, 0, 15));  //*i 把 i 指向的東西拿出來 (***)

    Object* p4;
    p4 = new NPC("Dumbledore__鄧不利多", "Hi, Potter! Finally see you ha!\nHere's all the things I have.\nHope these can to help you to defeat Voldemort, Good luck...\n", NPC_item_v);
    vector<Object*> obj4;
    obj4.push_back(p4);
    rooms.push_back(Room(false, 4, obj4));



    // Room[5] : Voldemort
    Object* p5;
    p5 = new Monster("Voldemort", 100, 50, 10);  // 因為Monster constructor
    vector<Object*> obj5;
    obj5.push_back(p5);  //**p4被推進去vector以後，因為vector會複製一份，所以p4在要去令新的東西的時候可以再拿去指新的東西
    rooms.push_back(Room(true, 5, obj5));



    //set the relatively places between the rooms
    rooms[0].setUpRoom(&rooms[1]);

    rooms[1].setDownRoom(&rooms[0]);
    rooms[1].setRightRoom(&rooms[2]);
    rooms[1].setUpRoom(&rooms[3]);

    rooms[2].setLeftRoom(&rooms[1]);

    rooms[3].setDownRoom(&rooms[1]);
    rooms[3].setUpRoom(&rooms[4]);

    rooms[4].setDownRoom(&rooms[3]);
    rooms[4].setLeftRoom(&rooms[5]);

    rooms[5].setRightRoom(&rooms[4]);

    //**after the room be created, remember to set the current room for the player
    player.setCurrentRoom(&rooms[0]);
    player.setPreviousRoom(&rooms[0]);
}

bool Dungeon::checkMonsterRoom( )
{
    vector<Object*> obj = player.getCurrentRoom()->getObjects();
    for( auto x : obj )
    {
        if( x->getTag() == "Monster" )
            return true;
    }
    return false;
}

/* Deal with the player's action     */
/* including showing the action list */
/* that player can do at that room   */
/* and dealing with player's input   */
void Dungeon::chooseAction() //傳入 vector<Object*> QQ 的說
{
    cout<<"What do you want to do?"<<endl  //
    <<"A. Move"<<endl;
    if( checkMonsterRoom() )
        cout<<"(cuz this is a monster room, \nso your next movement can only be retreating \nto the previous room until you defeat the monster.)\n\n";
    cout<<"B. Check Status"<<endl
    <<"C. Interact with the \"surprise\" in this room XD"<<endl
    <<"D. Save to file"<<endl;

    char di;
    cin>>di;
    cout<<"\n\n"; //cout when there is cin

    if( di == 'A' )
    {
        handleMovement();
    }
    else if( di == 'B' )
    {
        player.triggerEvent(&player);
    }
    else if( di == 'C' )
    {
        if( player.getCurrentRoom()->getObjects().empty() )
        {
            cout<<"There is nothing in this room~~"<<endl;
            return;
        }
        handleEvent(&player);
    }
    else if( di == 'D' )
    {
        cout<<"Are you sure to save and end this game?\n"
        <<"A. yes\n"
        <<"B. no\n";
        char d;
        cin>>d;
        if( d == 'A' )
        {
            Record r;
            r.saveToFile(&player, rooms);
            cout<<"successfully saved!  see ya!\n";
            exit(0);  //end all code here
        }
        else if( d == 'B' )
        {
            return;
        }
        else
        {
            cout<<"\nenter invalid\n";
            return;
        }

    }
    else
    {
        cout<<"\nenter invalid\n";
        return;
    }

    //可以不寫 else 的
};



void Dungeon::handleRetreat()
{
    player.changeRoom( player.getPreviousRoom() );
}


/* Deal with player's moveing action */
void Dungeon::handleMovement() // all things about movement needed to be deal with here
{                     //外部迴圈怎麼呼叫是他們的事，所有當玩家想要移動時的使用者介面要在這裡寫

    char di;

    if( checkMonsterRoom() )
    {
        handleEvent(&player);
    }
    else  //not moonster room
    {
        cout<<"Where do you want to go?"<<endl
        <<"A. Go up"<<endl
        <<"B. Go down"<<endl
        <<"C. Go left"<<endl
        <<"D. Go right"<<endl
        <<"E. Cancel"<<endl;
        cin>>di;
        cout<<"\n\n";

        if( di == 'A' )
        {
            if( (player.getCurrentRoom()-> getUpRoom() == NULL) )  // object 的 address 可以指向我要的function，就不用星星再.了
            {
                cout<<"there is no room!";
            }
            else  //there is room
            {
                player.changeRoom(player.getCurrentRoom()-> getUpRoom());  // pass the new room in
            }
        }
        else if( di == 'B' )
        {
            if( (player.getCurrentRoom()-> getDownRoom() == NULL) )
            {
                cout<<"there is no room!";
            }
            else  //there is room
            {
                player.changeRoom(player.getCurrentRoom()-> getDownRoom());
            }
        }
        else if( di == 'C' )
        {
            if( (player.getCurrentRoom()-> getLeftRoom() == NULL) )
            {
                cout<<"there is no room!";
            }
            else  //there is room
            {
                player.changeRoom(player.getCurrentRoom()-> getLeftRoom());
            }
        }
        else if( di == 'D' )
        {
            if( (player.getCurrentRoom()-> getRightRoom() == NULL) )
            {
                cout<<"there is no room!";
            }
            else  //there is room
            {
                player.changeRoom(player.getCurrentRoom()-> getRightRoom());
            }
        }
        else if( di == 'E' )
        {
            return;  // directly return
        }
        else
        {
            cout<<"\nenter invalid\n";
            return;
        }
    }
    return;  // return here****
}


/* Deal with player's interaction with objects in that room */
void Dungeon::handleEvent(Object* pp)  // 傳入的變數是 Player 的 pointer
{
    // 1. find the "room" that the player in first
    // 2. get all the object in the room then ( use the get function in Room then
    // 3. use the objects' trigger event function and pass the player pointer in

    //pp need to down cast first
    Player *p = dynamic_cast<Player*>(pp);
    Room *cr = p->getCurrentRoom();
    vector<Object*> obj = cr->getObjects();

    //told the player what's in this "room"

    for( auto x : obj )
    {
        cout<<"There is a/an "<<x->getTag()<<" \""<<x->getName()<<"\" in this room."<<endl;  // x is pointer type! use -> to access member or function
         x -> triggerEvent(p);
    }
        // 其實所有傳進來的變數型態都是player，但在後面的func 中對player值進行操作時，都要down cast一次 = =

};


/* Check whether the game should end or not */
/* Including player victory, or he/she dead */
bool Dungeon::checkGameLogic()  //**目前只check遊戲結束** when 1.玩家死掉  2.是出口房且房間內怪物死掉了
{
    if( player.getCurrentHealth() <= 0 ) //player dead -> game over
    {
        PlaySound(NULL, NULL, SND_FILENAME);

        cout<<"Game Over, you lose"<<endl;
        mciSendString(TEXT("open lose.mp3 alias lose"), NULL, 0, NULL);
        mciSendString(TEXT("play lose repeat"), NULL, 0, NULL);
        Sleep(2000);
        mciSendString(TEXT("close lose"), NULL, 0, NULL);

        mciSendString(TEXT("open evil.mp3 alias evil"), NULL, 0, NULL);
        mciSendString(TEXT("play evil repeat"), NULL, 0, NULL);
        Sleep(2000);
        mciSendString(TEXT("close evil"), NULL, 0, NULL);

        return true;
    }
    else if( checkMonsterRoom() ) //monster dead -> pop the monster, and if the player is in the last room, victory
    {
        vector<Object*> obj = (player.getCurrentRoom()->getObjects());
        int i = 0;
        for( auto x : obj )
        {
            if( x->getTag() == "Monster" )
            {
                Monster *m = dynamic_cast<Monster*>(x);  //x 沒有 getCurrentHealth 的 function所以要downcast 下去
                if( m->getCurrentHealth() <= 0 )
                {
                     player.getCurrentRoom()->eraseObject(i);  //pop the monster first and **the index will -1
                     i--;
                     cout<<"\nYou have defeated the monster in this room!\n\n";
                     mciSendString(TEXT("open coin.mp3 alias coin"), NULL, 0, NULL);
                     mciSendString(TEXT("play coin repeat"), NULL, 0, NULL);
                     Sleep(1000);
                     mciSendString(TEXT("close coin"), NULL, 0, NULL);
                     player.triggerEvent(&player);
                     break;
                }
            }
            i++;
        }
    }

    if( ( !checkMonsterRoom() ) && (player.getCurrentRoom()->getIsExit() == true) )  //is not the monster room && is Exist noe
    {
        cout<<"\nYou have finished all game!\nVictory!!\n"<<endl;
        PlaySound(NULL, NULL, SND_FILENAME);

        mciSendString(TEXT("open final.mp3 alias final"), NULL, 0, NULL);
        mciSendString(TEXT("play final repeat"), NULL, 0, NULL);
        Sleep(20000);
        mciSendString(TEXT("close final"), NULL, 0, NULL);

        return true;
    }  //the last room is monster room

    cout<<"\n\n";

    return false;  //other situation: return false, the game not yet over
};



/* Deal with the whole game process */
void Dungeon::runDungeon()
{
    //PlaySound(TEXT("C:\\Users\\Yoona\\Desktop\\Happy 2\\dungeon\\Dungeon\\Dungeon HP_2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
 
    PlaySound(TEXT("HP.wav"), NULL, SND_ASYNC | SND_LOOP);
    startGame();

    while(1)  //while true
    {
        chooseAction();  //deal with the interaction too
        //cout<<"\n\n";
        if( checkGameLogic() )  //while check game logic is true: game over
        {
            //mciSendString(TEXT("close HP"), NULL, 0, NULL);
            break;
        }
    }
};
