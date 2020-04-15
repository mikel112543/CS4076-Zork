//
// Created by Michael on 31/03/2020.
//

#include "item.h"

Item::Item(string name, string description) {
    this->name = name;
    this->description = description;
}

Item::Item(string newName, string description, bool weaponCheck) {
    this->name = newName;
    this->description = description;
    weaponCheck = true;
}
string Item::getShortDescription() {
    return name + ": " + description;
}

string Item::getDescription() {
    return description;
}

string Item::getName()  {
    return name;
}
