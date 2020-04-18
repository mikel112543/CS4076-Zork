#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>
#include <vector>
#include "item.h"

using namespace std;

// No need to include room since we're only working with pointers.
// This is how we tell the compiler "there will be a room eventually".
// This is called a "forward declaration".
class Room;

class Character
{
public:
    Character(string name);
    Character(string name, int health, int stamina, bool isEnemy, bool roaming);

    string getName();
    int    getHealth();
    int    getStamina();
    Room  *getCurrentRoom();
    string displayInventory();
    void setName(string name);
    void setHealth(int setHealth);
    void setStamina(int stamina);
    void setCurrentRoom(Room* next);
    void addToInventory(Item* newItem);
    void removeFromInventory(string itemName);
    bool itemInInventory(string itemName);
    void Move(Character *enemy);
    bool roamingCheck(Character *enemy);



private:
    string name;
    int health;
    int stamina;
    bool roaming;
    bool isEnemy;
    Room *currentRoom;
    vector<Item> Inventory;
    string directions[4] = {"north", "east", "south", "west"};


};

#endif // CHARACTER_H
