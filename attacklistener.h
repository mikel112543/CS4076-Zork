//
// Created by Michael on 10/04/2020.
//
#include "eventlistener.h"

#ifndef ATTACKLISTENER_H
#define ATTACKLISTENER_H

class Game;

class AttackListener : public EventListener {

public:
    AttackListener(Game *game);
    void run(void *args) override;

private:
    Game *game;
};

#endif //ATTACKLISTENER_H
