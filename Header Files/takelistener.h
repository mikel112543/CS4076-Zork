//
// Created by Michael on 31/03/2020.
//

#include "eventlistener.h"

#ifndef TAKELISTENER_H
#define TAKELISTENER_H

class Game;

class TakeListener : public EventListener {

public:
    TakeListener(Game *game);
    void run(void *args) override;
private:
    Game *game;

};
#endif //TAKELISTENER_H
