//
// Created by Michael on 31/03/2020.
//

#ifndef ITEM_H
#define ITEM_H

#include<string>
#include "room.h"

using namespace std;

class Item {

public:
    Item(string newName, string description, bool weaponCheck);
    Item(string name, string description);
    string getShortDescription();
    string getDescription();
    string getName();


    //string getName();
    //Room *getCurrentRoom();


    // void setName(string name);
    //void setCurrentRoom(Room *next);

   // void setName(const string &name);

private:
    string name;
    string description;


};



#endif //ITEM_H
