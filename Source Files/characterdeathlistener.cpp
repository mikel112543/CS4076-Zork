#include <iostream>
#include "characterdeathlistener.h"
#include "eventmanager.h"
#include "game.h"

CharacterDeathListener::CharacterDeathListener(Game *game)
{
    this->game = game;
}

void CharacterDeathListener::run(void *args)
{
    if (game->is_over()) {
        return;
    }

    auto *player = (Player *) args;

    if (player->getName() == game->getPlayer().getName()) {
        EventManager::getInstance().trigger("defeat");
    }
}
