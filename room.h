#ifndef ROOM_H
#define ROOM_H

#include<map>
#include<string>
#include <debug/vector>


using namespace std;

class Item;
class Enemy;

class Room
{
public:
    Room(string name);
    Room(string name, bool isLocked);


    string getName();
    void setExits(Room *north, Room *east, Room *south, Room *west);
    Room *getExit(string direction);
    void addItem(Item *newItem);
    void removeItem(string itemName);
    void addEnemy(Enemy *newEnemy);
    void setName(string name);
    //void removeEnemy(string enemyName);
    int numberOfItems();
    string displayItem();
    string displayEnemy();
    string itemDescription(string itemName);
    bool isItemInRoom(string itemName);
    bool lockCheck(Room* room);
    bool unlock(Room *room);



private:
    string name;
    bool isLocked;
    map<string, Room *> exits;
    vector <Item> itemsInRoom;
    vector <Enemy> enemiesInRoom;



};

#endif // ROOM_H
