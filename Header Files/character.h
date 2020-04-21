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

class Character {

public:
    Character();
    Character(string name);
    ~Character();

    string getName();
    int getHealth();
    int getStamina();
    Room *getCurrentRoom();
    string displayInventory();
    virtual void setHealth(int health);
    void setStamina(int stamina);
    void setCurrentRoom(Room* next);
    void addToInventory(Item* newItem);
    void removeFromInventory(string itemName);
    bool itemInInventory(string itemName);

private:
    string name;
    int health;
    int stamina;
    Room *currentRoom;
    vector<Item> Inventory;
};


class Enemy : public Character {

public:
    Enemy(string name, int health, int stamina, bool isEnemy, bool roaming);
    ~Enemy();
    bool roamingCheck();
    void Move(Enemy *enemy);
    void setHealth(int health);

private:
    string name;
    int health;
    int stamina;
    bool isEnemy;
    bool roaming;
    Room *currentRoom;
};

#endif // CHARACTER_H
