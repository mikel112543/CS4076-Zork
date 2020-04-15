//
// Created by Michael on 10/04/2020.
//

#include <iostream>
#include "attacklistener.h"
#include "eventmanager.h"
#include "game.h"

AttackListener::AttackListener(Game *game) {
    this->game = game;
}

void AttackListener::run(void *args_ptr) {
    if(game->is_over()) {
        return;
    }
    auto *args = (vector<string> *) args_ptr;
    Enemy *enemy = (Enemy*) args;

    if(args->size() > 1) {
        game->attack(args->at(1));
    }else {
        cout << "That is not an enemy" << endl;
    }
}