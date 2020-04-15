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
#include "enterroomlistener.h"
#include "victorylistener.h"
#include "defeatlistener.h"
#include "takelistener.h"
#include "damagelistener.h"
#include "enemy.h"
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
    EventManager::getInstance().listen("enterRoom", new EnterRoomListener(this));
    EventManager::getInstance().listen("victory", new VictoryListener(this));
    EventManager::getInstance().listen("defeat", new DefeatListener(this));
    EventManager::getInstance().listen("damage", new DamageListener(this));


    rooms.push_back(new Room("A")); // 0
    rooms.push_back(new Room("B", false)); // 1
    rooms.push_back(new Room("C", false)); // 2
    rooms.push_back(new Room("D")); // 3
    rooms.push_back(new Room("E", false)); // 4
    rooms.push_back(new Room("F")); // 5
    rooms.push_back(new Room("G")); // 6
    rooms.push_back(new Room("H")); // 7
    rooms.push_back(new Room("I")); // 8
    rooms.push_back(new Room("J")); // 9

    rooms[0]->addItem(new Item("potion", "A strange elixir. I wonder what happens if i drink it?"));
    rooms[0]->addItem(new Item("skull", "Very freaky looking thing"));
    rooms[0]->addItem(new Item("key", "Oh a key. This might be useful on my adventure"));


    enemies.push_back(new Enemy("dragon", 50, 80, "A fire breathing dragon from the depths of Hellheim!", false));  //0
    enemies.push_back(new Enemy("goblin", 20, 50, "An ugly creature appears from the shadows", true));  //1
    enemies.push_back(new Enemy("zombie", 20, 50, "A human both dead inside and out", false));   //2





    /*items.push_back(new Item("key", "Oh a key. This might be useful on my adventure"));
    items.push_back(new Item("Juggernog","A strange elixir. I wonder what happens if I drink it "));
    items.push_back(new Item("Skull of Nan Sapwe", "A freaky looking skull"));
    items.push_back(new Item("Lightening Bow", "A bow infused with the lightening from Zeus himself!", true));
    items.push_back(new Item("Void Bow", "A bow capable of opening the gates of Hell! ", true));
     */


    /*Item *key = new Item("key");
    Item *juggernog = new Item( "Juggernog");
    Item *skull = new Item("Skull of Nan Sapwe");
    Item *lighteningBow = new Item("Lightening Bow");
    Item *voidBow = new Item("Void Bow");
     */


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

    enemies[0]->setCurrentRoom(rooms[1]);
    enemies[1]->setCurrentRoom(rooms[0]);
    enemies[2]->setCurrentRoom(rooms[2]);

    cout << "Welcome to Zork!" << endl;

    if (show_update) {
        update_screen();
    }
}

void Game::setOver(bool over) {
    this->gameOver = over;
}

void Game::map() {
    string names[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    string playerLocation = "[" + player.getCurrentRoom()->getName() + "]";

    for (int i = 0; i < rooms.size(); i++) {
        if (player.getCurrentRoom() == rooms[i]) {
            player.getCurrentRoom()->setName(playerLocation);          //add [] to players current room
        }
        for (int j = 0; j < enemies.size(); j++) {
            if (enemies[j]->getCurrentRoom() == rooms[i] &&
                rooms[i]->getName() != ("!" + rooms[i]->getName() + "!")) {
                enemies[j]->getCurrentRoom()->setName("!" + enemies[j]->getCurrentRoom()->getName() + "!");     // add !! to enemies cuu
            }
        }
    }

    cout << left << rooms[3]->getName() << "--- " << rooms[4]->getName() << "--- " << rooms[5]->getName() << endl;
    cout << "      |" << endl;
    cout << left << " " << rooms[1]->getName() << "--- " << rooms[0]->getName() << "--- " << rooms[2]->getName()
         << endl;
    cout << "      |" << endl;
    cout << left << " " << rooms[6]->getName() << "--- " << rooms[7]->getName() << "--- " << rooms[8]->getName()
         << endl;
    cout << "      |" << endl;
    cout << "      " << rooms[9]->getName() << endl;

    /*cout << "     -------              -------                 ------- " << endl;
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
        if (!next->lockCheck(next)) {        //check for no lock on door
            player.setCurrentRoom(next);
            player.setStamina(player.getStamina() - 1);
            EventManager::getInstance().trigger("enterRoom", next);
            for (auto &enemy : enemies) {
                if (enemy->roamingCheck(enemy)) {
                    enemy->Move(enemy);
                    enemy->setStamina(enemy->getStamina() - 1);
                }
            }
        } else {
            if (player.itemInInventory("key")) {     //check for possession of key
                cout << "This door is locked but you have a key! Hooray!" << endl;
                cout << "Unlocking door..." << endl;
                next->unlock(next);
                player.setCurrentRoom(next);
                player.removeFromInventory("key");
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
        EventManager::getInstance().trigger("takeItem", nullptr);
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

void Game::update_screen() {
    if (!gameOver) {
        Room *currentRoom = player.getCurrentRoom();

        cout << endl;
        cout << "You are in " << currentRoom->getName() << endl;
        //cout << "No. of items in this room = " << currentRoom->numberOfItems() << endl;
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
        for (int i = 0; i < enemies.size(); i++) {
            if (player.getCurrentRoom() == enemies[i]->getCurrentRoom()) {
                cout << enemies[i]->getName() << " HP: " << enemies[i]->getHealth() << " " << enemies[i]->getName()
                     << " ST: " << enemies[i]->getStamina() << endl;
            }
        }
    } else {
        cout << R"(Type "restart" or "exit".)" << endl;
    }
}
