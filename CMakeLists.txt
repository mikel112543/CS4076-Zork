cmake_minimum_required(VERSION 3.15)
project(Zork_Plain_Text)

set(CMAKE_CXX_STANDARD 14)

include_directories("Header Files")

add_executable(Zork_Plain_Text
        "Header Files/character.h"
        "Header Files/characterdeathlistener.h"
        "Header Files/defeatlistener.h"
        "Header Files/enterroomlistener.h"
        "Header Files/eventlistener.h"
        "Header Files/eventmanager.h"
        "Header Files/exitlistener.h"
        "Header Files/game.h"
        "Header Files/golistener.h"
        "Header Files/infolistener.h"
        "Header Files/inputlistener.h"
        "Header Files/maplistener.h"
        "Header Files/restartlistener.h"
        "Header Files/room.h"
        "Header Files/teleportlistener.h"
        "Header Files/victorylistener.h"
        "Source Files/character.cpp"
        "Source Files/characterdeathlistener.cpp"
        "Source Files/defeatlistener.cpp"
        "Source Files/enterroomlistener.cpp"
        "Source Files/eventmanager.cpp"
        "Source Files/exitlistener.cpp"
        "Source Files/game.cpp"
        "Source Files/golistener.cpp"
        "Source Files/infolistener.cpp"
        "Source Files/inputlistener.cpp"
        "Source Files/main.cpp"
        "Source Files/maplistener.cpp"
        "Source Files/restartlistener.cpp"
        "Source Files/room.cpp"
        "Source Files/teleportlistener.cpp"
        "Source Files/victorylistener.cpp" "Source Files/item.cpp" "Header Files/item.h" "Source Files/takelistener.cpp" "Header Files/takelistener.h" "Source Files/damagelistener.cpp" "Header Files/damagelistener.h" "Source Files/enemy.cpp" "Header Files/enemy.h" "Source Files/attacklistener.cpp" "Header Files/attacklistener.h")
