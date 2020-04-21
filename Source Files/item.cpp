//
// Created by Michael on 31/03/2020.
//

#include "item.h"

#include <utility>

Item::Item(string name, string description) {
    this->name = std::move(name);
    this->description = std::move(description);
}

Item::~Item() {

}

string Item::getDescription() {
    return description;
}

string Item::getName()  {
    return name;
}
