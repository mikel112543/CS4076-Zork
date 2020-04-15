//
// Created by Michael on 31/03/2020.
//

#include <iostream>
#include "takelistener.h"
#include "eventmanager.h"
#include "game.h"

TakeListener::TakeListener(Game *game)
{
    this->game = game;
}

void TakeListener::run(void *args_ptr) {
    if(game->is_over()) {
        return;
    }
    auto *args = (vector<string> *) args_ptr;
    Item *item = (Item *) args;

    if(args->size() > 1) {
        game->take(args->at(1));
    }else {
        cout << "That is not an item" << endl;
    }
}
