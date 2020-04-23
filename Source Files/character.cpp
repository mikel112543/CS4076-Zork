#include "character.h"

#include "eventmanager.h"
#include "item.h"
#include "room.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <memory>


Character::Character(const string &name, int health, int stamina){
    this->name = name;
    this->health = health;
    this->stamina = stamina;
}

Character::Character(string name)
{
    this->name  = name; // We need to use "this->" to differentiate between the "name" argument and the "name" from the class.
    health      = 100;
    stamina     = 100;
    currentRoom = nullptr;
}

Character::~Character() {

    std::cout<<"\n Character deleted \n";

}

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
    Inventory.push_back(newItem);
}

void Character::removeFromInventory(string itemName) {
    for(int i = 0; i < Inventory.size(); i++) {
        if(Inventory[i]->getName() == itemName) {
            Inventory.erase(Inventory.begin()+i);
            break;
        }
    }
}

string Character::displayInventory() {
    string tempString = "Inventory: ";
    for(auto & i : Inventory) {
        tempString += i->getName() + ", ";
    }
    return tempString;
}

bool Character::itemInInventory(string itemName) {
    if(Inventory.empty()) {
        return false;
    }else{
        for(auto & i : Inventory) {
            if(itemName == i->getName()) {
                return true;
            }
        }
    }
    return false;
}

Enemy::Enemy(const string &name, int health, int stamina, bool _roaming) : Character(name, health, stamina), roaming(_roaming){
    this->name = name;
    this->health = health;
    this->stamina = stamina;
    this->roaming = _roaming;
}

Enemy::~Enemy() {

}

int Enemy::getHealth()
{
    return health;
}

void Enemy::setHealth(int health)
{
    if (health <= 0) {
        health = 0;
        EventManager::getInstance().trigger("enemyDeath", this);
    }

    this->health = health;
}

bool Enemy::roamingCheck() {
    return roaming;
}


void Enemy::Move(Enemy *enemy) {
    vector<string> directions {"north", "east", "south", "west"};
    Room *next;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();       //create time based seed for shuffle

    std::shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));   //shuffle directions
    for(auto & direction : directions) {
        next = enemy->getCurrentRoom()->getExit(direction);
        if(next != nullptr) {                                   //check exit isn't dead end
            if(!next->lockCheck()) {                            //check exit isn't locked
                enemy->setCurrentRoom(next);                    //move if satisfies
                break;
            }
        }
    }
}






