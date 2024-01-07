
//
// Created by Qami on 12/22/2023.
//
#include "global.h"

int DURATION_OPEN_DOOR = 5000;
int DURATION_NEXT_GHOST = 5000;
vector<int> DURATION_FRIGHT = {6, 5, 4, 3, 2, 5, 2, 2, 1, 5, 2, 1, 1, 3, 1, 1, 1, 1, 0, 0, 0};
vector<position> possibleDirections = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // UP, LEFT, DOWN, RIGHT
vector<entities> ghostTypes = {GHOST, SCATTER_GHOST, FRIGHTENED_GHOST, EATEN_GHOST};
map<int, vector<int>> modeTimings = {{1, {7, 20, 7, 20, 5, 20, 5, 0}},  // LEVEL 0 - 1
                                     {4, {7, 20, 7, 20, 5, 17, 5, 0}},  // LEVEL 2 - 4
                                     {5, {5, 20, 5, 20, 5, 17, 5, 0}}}; // LEVEL 5+;

directions intToDirections(int i) {
    switch (i) {
    case 0:
        return UP;
    case 1:
        return LEFT;
    case 2:
        return DOWN;
    case 3:
        return RIGHT;
    default:
        return UP;
    }
}

directions eventToDirections(events e) {
    switch (e) {
    case MOVE_UP:
        return UP;
    case MOVE_LEFT:
        return LEFT;
    case MOVE_DOWN:
        return DOWN;
    case MOVE_RIGHT:
        return RIGHT;
    default:
        return UP;
    }
}

directions operator!(directions d) {
    switch (d) {
    case UP:
        return DOWN;
    case LEFT:
        return RIGHT;
    case DOWN:
        return UP;
    case RIGHT:
        return LEFT;
    default:
        return UP;
    }
}

events entityToEvents(entities e) {
    switch (e) {
    case COIN:
        return COIN_COLLECTED;
    case FRUIT:
        return FRUIT_EATEN;
    case GHOST:
    case PACMAN:
        return ATTACKED;
    default:
        return NONE;
    }
}

colors intToColors(int i) {
    switch (i) {
    case 0:
        return red;
    case 1:
        return pink;
    case 2:
        return blue;
    case 3:
        return orange;
    default:
        return red;
    }
}

int intToTiming(int i) {
    for (const auto& mode : modeTimings) {
        if (i <= mode.first)
            return mode.first;
    }
    return modeTimings.end()->first;
};

bool operator==(position p, position p1) { return p.x == p1.x && p.y == p1.y; }

bool operator!=(position p, position p1) { return p.x != p1.x || p.y != p1.y; }
