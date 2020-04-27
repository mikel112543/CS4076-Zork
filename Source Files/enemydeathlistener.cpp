//
// Created by Michael on 20/04/2020.
//

#include <iostream>
#include "enemydeathlistener.h"

#include "eventmanager.h"
#include "game.h"

EnemyDeathListener::EnemyDeathListener(Game *game)
{
    this->game = game;
}

void EnemyDeathListener::run(void *args)
{
    if (game->is_over()) {
        return;
    }

    auto *enemy = (Enemy *) args;

    game->removeEnemy(enemy->getName());                    //remove enemy from game when health == 0;
    cout << "You killed the " + enemy->getName() << endl;
    delete enemy;
}
