//
// Created by Michael on 31/03/2020.
//

#include <iostream>
#include "item.h"


Item::Item(string name, string description) : name(std::move(name)), description(std::move(description)) {}
/***********
 * 1. Destructors
 * Destroy item when out of scope
 */
Item::~Item() {

    std::cout<<"\n Item deleted \n";
}

string Item::getDescription() {
    return description;
}

string Item::getName()  {
    return name;
}

Weapon::Weapon(string name, string description, int damage) : Item(std::move(name), std::move(description)), damage(damage) {}

Weapon::~Weapon() {
    std::cout<<"\n Weapon deleted \n";
}

int Weapon::getDamage() {
    return damage;
}

/*int Weapon::operator*() {
    damage = damage * 2;
}
 */
