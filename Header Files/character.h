#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>
#include <vector>
#include "item.h"

using namespace std;

// No need to include room since we're only working with pointers.
// This is how we tell the compiler "there will be a room eventually".
// This is called a "forward declaration".

class Character {

public:
    Character(const string &_name, int _health, int _stamina);
    /**********
     * 7. Virtual functions and polymorphism
     */
    virtual ~Character();
    string getName();
    int getHealth() const;
    int getStamina()const;
    Room *getCurrentRoom();
    /***********
     * 8. Abstract classes and pure virtual functions
     * Character is abstract class
     * @param _health
     */
    virtual void setHealth(int _health) = 0;
    virtual void setStamina(int _stamina) = 0;
    void setCurrentRoom(Room* next);

private:
    string name;

protected:
    int health;
    int stamina;
    Room *currentRoom;
};

class Player : public Character {

public:
    Player(const string &name);
    ~Player() override;
    string displayInventory();
    void addToInventory(const string& itemName);
    void removeFromInventory(const string& itemName);
    bool itemInInventory(const string& itemName);
    virtual void setHealth(int _health) override;
    virtual void setStamina(int _stamina) override;

private:
    vector<Item*> Inventory;
};

class Enemy : public Character {

public:
    Enemy(const string &name, int health, int stamina, bool _roaming);
    ~Enemy() override;
    bool roamingCheck() const;
    void Move(Enemy *enemy);
    virtual void setHealth(int _health) override;
    virtual void setStamina(int _stamina) override;

private:
    bool roaming;
};

#endif // CHARACTER_H
