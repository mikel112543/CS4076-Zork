#include "game.h"

#include<ctime>
#include<iostream>

#include "eventmanager.h"
#include "room.h"
#include "item.h"

#include "golistener.h"
#include "maplistener.h"
#include "infolistener.h"
#include "restartlistener.h"
#include "teleportlistener.h"
#include "exitlistener.h"
#include "characterdeathlistener.h"
#include "enemydeathlistener.h"
#include "enterroomlistener.h"
#include "victorylistener.h"
#include "defeatlistener.h"
#include "takelistener.h"
#include "damagelistener.h"
#include "attacklistener.h"

Game::Game() :

        player("Hero") {
    srand(time(nullptr));

    // Commands
    EventManager::getInstance().listen("go", new GoListener(this));
    EventManager::getInstance().listen("map", new MapListener(this));
    EventManager::getInstance().listen("info", new InfoListener(this));
    EventManager::getInstance().listen("restart", new RestartListener(this));
    EventManager::getInstance().listen("teleport", new TeleportListener(this));
    EventManager::getInstance().listen("exit", new ExitListener(this));
    EventManager::getInstance().listen("take", new TakeListener(this));
    EventManager::getInstance().listen("attack", new AttackListener(this));

    // State changes
    EventManager::getInstance().listen("characterDeath", new CharacterDeathListener(this));
    EventManager::getInstance().listen("enemyDeath", new EnemyDeathListener(this));
    EventManager::getInstance().listen("enterRoom", new EnterRoomListener(this));
    EventManager::getInstance().listen("victory", new VictoryListener(this));
    EventManager::getInstance().listen("defeat", new DefeatListener(this));
    EventManager::getInstance().listen("damage", new DamageListener(this));

    rooms.push_back(new Room("A")); // 0
    rooms.push_back(new Room("B" )); // 1
    rooms.push_back(new Room("C")); // 2
    rooms.push_back(new Room("D" )); // 3
    rooms.push_back(new Room("E" )); // 4
    rooms.push_back(new Room("F" )); // 5
    rooms.push_back(new Room("G")); // 6
    rooms.push_back(new Room("H")); // 7
    rooms.push_back(new Room("I")); // 8
    rooms.push_back(new Room("J", true)); // 9

    rooms[0]->addItem(new Item("potion", "A strange elixir. You feel stronger than ever!"));
    rooms[4]->addItem(new Item("skull", "Very freaky looking thing"));
    rooms[6]->addItem(new Item("key", "Oh a key. This might be useful on my adventure"));

    enemies.push_back(new Enemy( "dragon", 10, 80, true, false));  //0
    enemies.push_back(new Enemy( "goblin", 20, 50, true, true));  //1
    //enemies.push_back(new Character("zombie", 20, 50, true, true));
    //enemies.push_back(new Character("ogre", 20, 50, true, true));    //2

    //                 N                E               S               W
    rooms[0]->setExits(rooms[4], rooms[2], rooms[7], rooms[1]);
    rooms[1]->setExits(nullptr, rooms[0], nullptr, nullptr);
    rooms[2]->setExits(nullptr, nullptr, nullptr, rooms[0]);
    rooms[3]->setExits(nullptr, rooms[4], nullptr, nullptr);
    rooms[4]->setExits(nullptr, rooms[5], rooms[0], rooms[3]);
    rooms[5]->setExits(nullptr, nullptr, nullptr, rooms[4]);
    rooms[6]->setExits(nullptr, rooms[7], nullptr, nullptr);
    rooms[7]->setExits(rooms[0], rooms[8], rooms[9], rooms[6]);
    rooms[8]->setExits(nullptr, nullptr, nullptr, rooms[7]);
    rooms[9]->setExits(rooms[7], nullptr, nullptr, nullptr);


    reset();
}

void Game::reset(bool show_update) {
    gameOver = false;

    player.setCurrentRoom(rooms[0]);
    player.setHealth(100);
    player.setStamina(100);

    enemies[0]->setCurrentRoom(rooms[8]);
    enemies[1]->setCurrentRoom(rooms[3]);

    cout << "Welcome to Zork!" << endl;

    if (show_update) {
        update_screen();
    }
}

void Game::setOver(bool over) {
    this->gameOver = over;
}

void Game::mapUpdate() {
    string names[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

    for (int i = 0; i < rooms.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            if (player.getCurrentRoom() == rooms[i] && enemies[j]->getCurrentRoom() != rooms[i]) {
                rooms[i]->setName("[" + names[i] + "]" );                                      //add [] to players current room
            } else if (enemies[j]->getCurrentRoom() == rooms[i] && player.getCurrentRoom() != rooms[i]) {
                rooms[i]->setName("!" + names[i] + "!");                                       //add !! to enemies current room
                j++;
            } else if (enemies[j]->getCurrentRoom() == rooms[i] && player.getCurrentRoom() == rooms[i]) {
                rooms[i]->setName("![" + names[i] +
                                  "]!");                                      //add ![]! to room with both enemies and player
                j++;
            }else {
                rooms[i]->setName(names[i]);
            }
        }
        if(enemies.empty() && player.getCurrentRoom() == rooms[i]) {
            rooms[i]->setName("[" + names[i] + "]");
        }
    }
}

void Game::map() {
    cout << rooms[3]->getName() << "--- " << rooms[4]->getName() << "---- " << rooms[5]->getName() << endl;
    cout << "      |" << endl;
    cout << rooms[1]->getName() << "--- " << rooms[0]->getName() << "---- " << rooms[2]->getName() << endl;
    cout << "      |" << endl;
    cout << " " << rooms[6]->getName() << "--- " << rooms[7]->getName() << "---- " << rooms[8]->getName() << endl;
    cout << "      |" << endl;
    cout << "      " << rooms[9]->getName() << endl;

    /*cout << "   -------                -------                 ------- " << endl;
    cout << "     |  D  |----------------|  E  |-----------------|  F  | " << endl;
    cout << "     -------                -------                 ------- " << endl;
    cout << "                               |                            " << endl;
    cout << "                               |                            " << endl;
    cout << "                               |                            " << endl;
    cout << "     -------                -------                 ------- " << endl;
    cout << "     |  B  |----------------|  A  |-----------------|  C  | " << endl;
    cout << "     -------                -------                 ------- " << endl;
    cout << "                               |                            " << endl;
    cout << "                               |                            " << endl;
    cout << "                               |                            " << endl;
    cout << "     -------                -------                 ------- " << endl;
    cout << "     |  G  |----------------|  H  |-----------------|  I  | " << endl;
    cout << "     -------                -------                 ------- " << endl;
    cout << "                               |                            " << endl;
    cout << "                               |                            " << endl;
    cout << "                               |                            " << endl;
    cout << "                            -------                         " << endl;
    cout << "                            |  J  |                         " << endl;
    cout << "                            -------                         " << endl;

    cout << "D-E-F" << endl;
    cout << "B-A-C" << endl;
    cout << "  |  " << endl;
    cout << "G-H-I" << endl;
    cout << "  |  " << endl;
    cout << "  J  " << endl;
     */
}

void Game::info() {
    cout << "Available commands:" << endl;
    cout << " - go <direction>" << endl;
    cout << " - teleport" << endl;
    cout << " - take <item>" << endl;
    cout << " - attack <enemy>" << endl;
    cout << " - map" << endl;
    cout << " - info" << endl;
}

void Game::go(string direction) {
    Room *next = player.getCurrentRoom()->getExit(direction);

    if (next != nullptr) {
        if (!next->lockCheck()) {        //check for no lock on door
            player.setCurrentRoom(next);
            player.setStamina(player.getStamina() - 1);
            EventManager::getInstance().trigger("enterRoom", next);
            for (auto enemy : enemies) {
                if (enemy->roamingCheck()) {        //check if enemy can roam
                    enemy->Move(enemy);
                    enemy->setStamina(enemy->getStamina() - 1);
                }
            }
        } else {
            if (player.itemInInventory("key")) {     //check for possession of key
                cout << "This door is locked but you have a key! Hooray!" << endl;
                cout << "Unlocking door..." << endl;
                next->unlock();                     //unlock door if key in inventory
                player.setCurrentRoom(next);
                player.removeFromInventory("key");
                EventManager::getInstance().trigger("enterRoom", next);
            } else {
                cout << "The room is locked and you have not got a key" << endl;
            }
        }
    } else {
        cout << "You hit a wall" << endl;
    }
}

void Game::teleport() {
    int selected = rand() % rooms.size();
    player.setCurrentRoom(rooms[selected]);
    player.setStamina(player.getStamina() - 50);
    EventManager::getInstance().trigger("enterRoom", rooms[selected]);
}

void Game::take(string itemName) {
    bool isThere = player.getCurrentRoom()->isItemInRoom(itemName);
    if (!isThere) {      //check if item is in room
        cout << "item is not in room";
    } else {
        player.addToInventory(new Item(itemName, player.getCurrentRoom()->itemDescription(itemName)));
        cout << "You have taken " + itemName << endl;
        cout << player.getCurrentRoom()->itemDescription(itemName) << endl;
        player.getCurrentRoom()->removeItem(itemName);
        EventManager::getInstance().trigger("damage", &itemName);  //triggers damage event
    }
}

void Game::attack(string enemyName) {
    for (int i = 0; i < enemies.size(); i++) {
        if (player.getCurrentRoom() == enemies[i]->getCurrentRoom() && enemyName == enemies[i]->getName()) {
            cout << "You attack the " + enemyName + " with a mighty fist!" << endl;
            enemies[i]->setHealth(enemies[i]->getHealth() - 10);
        }
    }
}

bool Game::is_over() {
    return gameOver;
}

Character &Game::getPlayer() {
    return player;
}

void Game::removeEnemy(string enemyName) {
    for(int i = 0; i < enemies.size(); i++) {
        if(enemyName == enemies[i]->getName()) {
            enemies.erase(enemies.begin()+i);
        }
    }
}

void Game::update_screen() {
    if (!gameOver) {
        mapUpdate();
        Room *currentRoom = player.getCurrentRoom();

        cout << endl;
        cout << "You are in " << currentRoom->getName() << endl;
        cout << currentRoom->displayItem() << endl;
        cout << player.displayInventory() << endl;
        string tempString = "Enemies in room: ";
        for (auto &i : enemies) {
            if (player.getCurrentRoom() == i->getCurrentRoom()) {
                cout << tempString + i->getName() << endl;
            }
        }

        cout << "Exits:";
        if (currentRoom->getExit("north") != nullptr) { cout << " north"; }
        if (currentRoom->getExit("east") != nullptr) { cout << " east"; }
        if (currentRoom->getExit("south") != nullptr) { cout << " south"; }
        if (currentRoom->getExit("west") != nullptr) { cout << " west"; }
        cout << endl;

        cout << "Player HP: " << player.getHealth() << " Player ST: " << player.getStamina() << endl;
        for(int i = 0; i < enemies.size(); i++) {
            if(currentRoom == enemies[i]->getCurrentRoom()) {
                cout << enemies[i]->getName() << " HP: " << enemies[i]->getHealth() << " " << enemies[i]->getName()
                     << " ST: " << enemies[i]->getStamina() << endl;
            }
        }
    } else {
        cout << R"(Type "restart" or "exit".)" << endl;
    }
}