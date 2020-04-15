#include "character.h"

#include "eventmanager.h"
#include "item.h"
#include "room.h"

Character::Character(string name)
{
    this->name  = name; // We need to use "this->" to differentiate between the "name" argument and the "name" from the class.
    health      = 100;
    stamina     = 100;
    currentRoom = nullptr;
}

/*Character::Character(string name, int health, int stamina, bool roaming) {
    this->name = name;
    this->health = health;
    this->stamina = stamina;
    this->roaming = roaming;
}
 */

string Character::getName()
{
    return name;
}

int Character::getHealth()
{
    return health;
}

int Character::getStamina()
{
    return stamina;
}

Room *Character::getCurrentRoom()
{
    return currentRoom;
}

void Character::setHealth(int health)
{
    if (health <= 0) {
        health = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }

    this->health = health;
}

void Character::setStamina(int stamina)
{
    if (stamina <= 0) {
        stamina = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }

    this->stamina = stamina;
}

void Character::setCurrentRoom(Room *next)
{
    currentRoom = next;
}

void Character::addToInventory(Item* newItem) {
    Inventory.push_back(*newItem);
}

void Character::removeFromInventory(string itemName) {
    for(int i = 0; i < Inventory.size(); i++) {
        if(Inventory[i].getName() == itemName) {
            Inventory.erase(Inventory.begin()+i);
            break;
        }
    }
}

string Character::displayInventory() {
    string tempString = "Inventory: ";
    for(auto & i : Inventory) {
        tempString += i.getName() + ", ";
    }
    return tempString;
}

bool Character::itemInInventory(string itemName) {
    if(Inventory.empty()) {
        return false;
    }else{
        for(auto & i : Inventory) {
            if(itemName == i.getName()) {
                return true;
            }
        }
    }
    return false;
}

