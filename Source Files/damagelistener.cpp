//
// Created by Michael on 02/04/2020.
//

#include "damagelistener.h"

#include<iostream>

#include "game.h"


// DamageListener.cpp
DamageListener::DamageListener(Game *game)
{
    this->game = game;
}

void DamageListener::run(void * args)
{
    if(game->is_over()) {
        return;
    }
    Item *item = (Item *) args;

    if(item->getName() == "skull") {
        game->getPlayer().setHealth(game->getPlayer().getHealth() - 75);    //triggered if skull is picked up
        game->getPlayer().removeFromInventory("skull");
        cout << endl;
        cout << "Ouch! You feel the skull damage your soul." << endl;
    }
}

