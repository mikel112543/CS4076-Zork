#ifndef GAME_H
#define GAME_H

#include<string>
#include<vector>

#include "character.h"
#include "room.h"

using namespace std;

class Game
{
public:
    Game();
    void reset(bool show_update = true);

    void map();
    void info();
    void go(string direction);
    void teleport();
    void take(string itemName);
    void attack(string enemyName);

    void update_screen();

    Character &getPlayer();
    void setOver(bool over);
    bool is_over();
    void setCurrentRoom(Room *next);

private:
    Character      player;
    vector<Room *> rooms;
    vector<Enemy *> enemies;
    bool           gameOver;



};
#endif // GAME_H
