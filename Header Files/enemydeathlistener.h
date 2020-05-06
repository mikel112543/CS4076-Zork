//
// Created by Michael on 20/04/2020.
//
#ifndef ENEMYDEATHLISTENER_H
#define ENEMYDEATHLISTENER_H

#include "eventlistener.h"

class Game;


class EnemyDeathListener : public EventListener
{
public:
    EnemyDeathListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};
#endif // ENEMYDEATHLISTENER_H
