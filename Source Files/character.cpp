#include "character.h"

#include "eventmanager.h"
#include "room.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

/************** 2. Inheritance (including virtual methods) and cascading constructors
 *
 *
 * @param _name - Character name
 * @param _health - Character health
 * @param _stamina - Character stamina
 */
Character::Character(const string &_name, int _health, int _stamina) : name(_name), health(_health), stamina(_stamina){ }

/**********
 * 1. Destructors
 */
Character::~Character() { std::cout<<"\n Character deleted \n"; }

string Character::getName() { return name; }

int Character::getHealth() const { return health; }

int Character::getStamina() const { return stamina; }

Room *Character::getCurrentRoom() { return currentRoom; }

void Character::setCurrentRoom(Room *next) { currentRoom = next; }

/**
 * 9. Initializer List
 * @param name - Player name
 */
Player::Player(const string& name) : Character(name, health, stamina)
{
                            // We need to use "this->" to differentiate between the "name" argument and the "name" from the class.
    health      = 100;
    stamina     = 100;
    currentRoom = nullptr;
}

Player::~Player() { std::cout<<"\n Player defeated \n";}

void Player::setStamina(int _stamina)
{
    if (_stamina <= 0) {
        stamina = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }
    stamina = _stamina;
}

void Player::setHealth(int _health)
{
    if (_health <= 0) {
        health = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }
    health = _health;
}

/**
 * 6. Friends (Player is friend of Room to access itemsInRoom vector to avoid heap allocation)
 * @param itemName - name of item to be added to players inventory
 */
void Player::addToInventory(const string& itemName) {
    Room *room = getCurrentRoom();
    for(auto & i : room->itemsInRoom) {
        if(i->getName() == itemName) {
            Inventory.push_back(i);
            break;
        }
    }

}

void Player::removeFromInventory(const string& itemName) {
    for(int i = 0; i < Inventory.size(); i++) {
        if(Inventory[i]->getName() == itemName) {
            Inventory.erase(Inventory.begin()+i);
            break;
        }
    }
}

string Player::displayInventory() {
    string tempString = "Inventory: ";
    for(auto & i : Inventory) {
        tempString += i->getName() + ", ";
    }
    return tempString;
}

bool Player::itemInInventory(const string& itemName) {
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
/**
 *
 * @param name
 * @param health
 * @param stamina
 * @param _roaming
 */
Enemy::Enemy(const string &name, int health, int stamina, bool _roaming) : Character(name, health, stamina), roaming(_roaming){ }

Enemy::~Enemy() {
    std::cout<<"\n Enemy defeated \n";
}

void Enemy::setStamina(int _stamina)
{
    if (_stamina <= 0) {
        stamina = 0;
        EventManager::getInstance().trigger("enemyDeath", this);
    }
    stamina = _stamina;
}

void Enemy::setHealth(int _health)
{
    if (_health <= 0) {
        health = 0;
        EventManager::getInstance().trigger("enemyDeath", this);
    }
    health = _health;
}

bool Enemy::roamingCheck() const {
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






