//
// Created by Michael on 08/04/2020.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

using namespace std;

class Room;
class Character;

class Enemy {
public:
    Enemy(string name, int health, int stamina, string description, bool roaming);
    string getName();
    int getHealth();
    int getStamina();
    void setStamina(int stamina);
    string getDescription();
    Room *getCurrentRoom();
    void setCurrentRoom(Room* next);
    void setHealth(int health);
    void Move(Enemy *enemy);
    bool roamingCheck(Enemy *enemy);


private:
    string name;
    int health;
    int stamina;
    string description;
    bool roaming;
    Room* currentRoom;
    string directions[4] = {"north", "east", "south", "west"};

};

#endif // ENEMY_H
