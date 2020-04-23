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

    Character(string name);
    Character(const string &name, int health, int stamina);
    ~Character();
    string getName();
    virtual int getHealth();
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
    Room *currentRoom;
    int health;
    int stamina;
    vector<Item*> Inventory;
};


class Enemy : public Character {

public:
    Enemy(const string &name, int health, int stamina, bool _roaming);
    ~Enemy();
    bool roamingCheck();
    void Move(Enemy *enemy);
    virtual int getHealth() override;
    virtual void setHealth(int health) override;

private:
    string name;
    int health;
    int stamina;
    bool roaming;
};

#endif // CHARACTER_H
