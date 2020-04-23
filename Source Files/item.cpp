//
// Created by Michael on 31/03/2020.
//

#include <iostream>
#include "item.h"


Item::Item(string name, string description) {
    this->name = std::move(name);
    this->description = std::move(description);
}

Item::~Item() {

    std::cout<<"\n Item deleted \n";
}

string Item::getDescription() {
    return description;
}

string Item::getName()  {
    return name;
}
