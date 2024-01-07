//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_GLOBAL_H
#define PAC_MAN_GLOBAL_H

#include <vector>
#include <map>

using namespace std;


// ENUMS

enum events {
    NONE,
    PLAY,
    MOVE_UP,
    MOVE_LEFT,
    MOVE_DOWN,
    MOVE_RIGHT,
    COIN_COLLECTED,
    FRUIT_EATEN,
    ATTACKED,
    GAME_OVER,
    VICTORY
};

enum directions {
    UP,
    LEFT,
    DOWN,
    RIGHT
};

enum entities {
    PACMAN,
    LOSER_PACMAN,
    WINNER_PACMAN,
    GHOST,
    FRIGHTENED_GHOST,
    SCATTER_GHOST,
    EATEN_GHOST,
    COIN,
    FRUIT,
    WALL,
    DOOR,
    EMPTY
};

enum colors {
    red,
    pink,
    blue,
    orange,
};

// ENUM CONVERTIONS

extern directions intToDirections(int i);

extern directions eventToDirections(events e);

extern directions operator!(directions d);

extern events entityToEvents(entities e);

extern colors intToColors(int i);

extern int intToTiming(int i);

// STRUCTS

struct position {
    int x, y;
};

extern bool operator==(position p, position p1);

extern bool operator!=(position p, position p1);


// VARIABLES

extern int DURATION_OPEN_DOOR;
extern int DURATION_NEXT_GHOST;
extern vector<int> DURATION_FRIGHT;
extern vector<position> possibleDirections;
extern vector<entities> ghostTypes;
extern map<int, vector<int>> modeTimings;


#endif //PAC_MAN_GLOBAL_H
