//
// Created by Qami on 11/28/2023.
//

#ifndef PAC_MAN_ENUM_H
#define PAC_MAN_ENUM_H

enum events {
    NONE,
    PLAY,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    COIN_COLLECTED,
    FRUIT_EATEN,
    GHOST_EATEN,
    GHOST_ATTACK,
    GAME_OVER,
    VICTORY
};

enum entities{
    PACMAN,
    LOSER_PACMAN,
    WINNER_PACMAN,
    GHOST,
    EATABLEGHOST,
    COIN,
    FRUIT,
    WALL,
    DOOR,
    EMPTY
};

enum collectable{
    coin,
    fruit
};

enum colors{
    blue,
    red,
    pink,
    purple,
    green,
    orange,
    none,
};
#endif //PAC_MAN_ENUM_H
