//
// Created by Michael on 02/04/2020.
//
#ifndef DAMAGELISTENER_H
#define DAMAGELISTENER_H

#include "eventlistener.h"

class Game;

class DamageListener : public EventListener {
public:
    DamageListener(Game *game);
    void run(void *args) override;

private:
    Game *game;
};

#endif //DAMAGELISTENER
