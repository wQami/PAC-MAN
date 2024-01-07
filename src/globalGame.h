//
// Created by Qami on 12/27/2023.
//

#ifndef PAC_MAN_GLOBALGAME_H
#define PAC_MAN_GLOBALGAME_H

#include "SFML/System/Vector2.hpp"
#include <string>

using namespace std;

// ENUMS

enum states { MENU, LEVEL, PAUSED, WON, LOST };

// STRUCTS

// VARIABLES

extern unsigned int SCREEN_WIDTH;
extern unsigned int SCREEN_HEIGHT;

extern int SCALE_SIZE;
extern int PACMAN_OFFSET_X;
extern int PACMAN_OFFSET_Y;
extern int PACMAN_SIZE;
extern int PACMAN_GAP;
extern int GHOST_OFFSET_X;
extern int GHOST_OFFSET_Y;
extern int GHOST_SIZE;
extern int GHOST_GAP;
extern int COIN_OFFSET_X;
extern int COIN_OFFSET_Y;
extern int COIN_SIZE;
extern int FRUIT_OFFSET_X;
extern int FRUIT_OFFSET_Y;
extern int FRUIT_SIZE;
extern int WALL_OFFSET;
extern int WALL_SIZE;
extern int WALL_GAP;
extern int LIFE_OCCUPATION;
extern int LIFE_DRAW_OFFSET;

extern int PACMAN_SPEED;
extern int PACMAN_ANIMATION_SPEED;
extern int GHOST_SPEED;
extern int FRIGHTENED_GHOST_SPEED;
extern int EATEN_GHOST_SPEED;
extern int DECREMENT_SPEED;

extern string PATH_IMAGES;
extern string PATH_FONTS;
extern string PATH_HIGHSCORES;
extern string PATH_TILEMAPS;
extern string IMAGE_SPRITE_TEXTURES;
extern string IMAGE_WALL_TEXTURES;
extern string IMAGE_PACMAN_LOGO;
extern string FONT_MASTER;
extern string HIGHSCORE_MASTER;

// FUNCTIONS
extern sf::Vector2<float> calcScale(int sizeObject, int scale);
extern float intToFloat(int i);
extern int roundToNearestInt(const double& toRound, const int& nearest);

#endif // PAC_MAN_GLOBALGAME_H
