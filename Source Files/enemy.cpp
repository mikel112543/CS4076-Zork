//
// Created by Michael on 08/04/2020.
//

#include "enemy.h"
#include "eventmanager.h"
#include "room.h"

Enemy::Enemy(string name, int health, int stamina, string description, bool roaming)
{
    this->name = name;
    this->health = health;
    this->stamina = stamina;
    this->description = description;
    this->roaming = roaming;
}

string Enemy::getName() {
    return name;
}

int Enemy::getHealth() {
    return health;
}

int Enemy::getStamina() {
    return stamina;
}

void Enemy::setStamina(int stamina) {
    this->stamina = stamina;
}

string Enemy::getDescription() {
    return description;
}

void Enemy::setHealth(int health) {
    this->health = health;

}

Room *Enemy::getCurrentRoom() {
    return currentRoom;
}

void Enemy::setCurrentRoom(Room *next) {
    currentRoom = next;
}

void Enemy::Move(Enemy *enemy) {
    int randNum = rand() % directions->size();
    Room *next = enemy->getCurrentRoom()->getExit(directions[randNum]);
    if (next == nullptr) {
        while (next == nullptr) {
            next = enemy->getCurrentRoom()->getExit(directions[rand() % directions->size()]);
        }
        enemy->setCurrentRoom(next);
    }else{
        enemy->setCurrentRoom(next);
    }
}

bool Enemy::roamingCheck(Enemy *enemy) {
    return roaming;
}






