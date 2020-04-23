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

    auto *character = (Character *) args;

    if (character->getName() == game->getPlayer().getName()) {
        EventManager::getInstance().trigger("defeat");
    }else{
        game->removeEnemy(character->getName());
        cout << "You killed the " + character->getName() << endl;
        delete character;
    }
    /*else if (character->enemyCheck()) {                            //check if character is enemy
        game->removeEnemy(character->getName());                    //remove enemy from game when health == 0;
        cout << "You killed the " + character->getName() << endl;
        delete character;                                           //USE OF DESTRUCTOR
    }
    */
}
