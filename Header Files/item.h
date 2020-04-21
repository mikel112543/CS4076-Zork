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
    Item(string name, string description);
    ~Item();
    string getDescription();
    string getName();

private:
    string name;
    string description;


};



#endif //ITEM_H
