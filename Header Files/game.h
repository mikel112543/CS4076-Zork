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
    void mapUpdate();
    void info();
    void go(string direction);
    void teleport();
    void take(string itemName);
    void attack(const string& enemyName);
    void removeEnemy(const string& enemyName);

    void update_screen();

    Player &getPlayer();
    void setOver(bool over);
    bool is_over();

private:
    vector<Room *> rooms;
    vector<Enemy *> enemies;
    Player      player;
    vector<Character*> bosses;
    bool           gameOver;

};
#endif // GAME_H
