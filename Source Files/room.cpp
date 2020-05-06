#include <iostream>
#include "room.h"
#include "item.h"

Room::Room(string name) :
    name(name)
{
    exits["north"] = nullptr;
    exits["east"]  = nullptr;
    exits["south"] = nullptr;
    exits["west"]  = nullptr;
}

Room::Room(string name, bool isLocked) :
        name(name)

{
    exits["north"] = nullptr;
    exits["east"]  = nullptr;
    exits["south"] = nullptr;
    exits["west"]  = nullptr;
    this->isLocked = isLocked;
}

string Room::getName()
{
    return name;
}

void Room::setName(string name) {
    this->name = name;
}

bool Room:: lockCheck() {
    return isLocked;
}

bool Room:: unlock() {
    return isLocked = false;
}


void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    exits["north"] = north;
    exits["east"]  = east;
    exits["south"] = south;
    exits["west"]  = west;
}
void Room::addItem(Item* newItem)
{
    itemsInRoom.push_back(newItem);
}

void Room::removeItem(string itemName) {
    for(int i = 0; i < itemsInRoom.size(); i++) {
        if(itemsInRoom[i]->getName() == itemName) {
            itemsInRoom.erase(itemsInRoom.begin() + i);         //erase item at point i
            break;
        }
    }
}

Room *Room::getExit(string direction)
{
    return exits[direction];
}

string Room::itemDescription(string itemName) {
    string description;
    for(int i = 0; i < itemsInRoom.size(); i++) {
        if(itemsInRoom[i]->getName() == itemName) {
            description = itemsInRoom[i]->getDescription();
        }
    }
    return description;
}

bool Room::isItemInRoom(string itemName) {
    if (itemsInRoom.empty()) {
        return false;
    } else {
        for( auto & i : itemsInRoom) {
            if(itemName == i->getName()) {   //loop to check if item is in vector
                return true;
            }
        }

    }
    return false;
}

string Room::displayItem() {
    string tempString = "Items in room: ";
    if(itemsInRoom.empty()) {
        tempString = "There are no items in this room";
    }else{
        for(auto & i : itemsInRoom)  {
            tempString += i->getName() + ", ";
        }
    }
    return tempString;
}






