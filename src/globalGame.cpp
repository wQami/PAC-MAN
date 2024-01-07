//
// Created by Qami on 12/27/2023.
//

#include "globalGame.h"
#include <cmath>

unsigned int SCREEN_WIDTH = 800u;
unsigned int SCREEN_HEIGHT = 600u;

int SCALE_SIZE = 40;
int PACMAN_OFFSET_X = 853;
int PACMAN_OFFSET_Y = 5;
int PACMAN_SIZE = 33;
int PACMAN_GAP = 17;
int GHOST_OFFSET_X = 1;
int GHOST_OFFSET_Y = 4;
int GHOST_SIZE = 35;
int GHOST_GAP = 15;
int COIN_OFFSET_X = 410;
int COIN_OFFSET_Y = 208;
int COIN_SIZE = 6;
int FRUIT_OFFSET_X = 601;
int FRUIT_OFFSET_Y = 3;
int FRUIT_SIZE = 36;
int WALL_OFFSET = 5;
int WALL_SIZE = 37;
int WALL_GAP = 10;
int LIFE_OCCUPATION = 30;
int LIFE_DRAW_OFFSET = 7;

int PACMAN_SPEED = 200;
int PACMAN_ANIMATION_SPEED = PACMAN_SPEED / 2;
int GHOST_SPEED = 190;
int FRIGHTENED_GHOST_SPEED = 500;
int EATEN_GHOST_SPEED = 100;
int DECREMENT_SPEED = 1000;

string PATH_IMAGES = "resources/images/";
string PATH_FONTS = "resources/fonts/";
string PATH_HIGHSCORES = "resources/highscores/";
string PATH_TILEMAPS = "resources/tilemaps/";
string IMAGE_SPRITE_TEXTURES = "Sprites.png";
string IMAGE_WALL_TEXTURES = "Walls.png";
string IMAGE_PACMAN_LOGO = "Pac-Man_Logo.png";
string FONT_MASTER = "emulogic.ttf";
string HIGHSCORE_MASTER = "highscores.txt";

sf::Vector2<float> calcScale(int sizeObject, int scale) {
    float result = static_cast<float>(scale) / static_cast<float>(sizeObject);
    return {result, result};
}

float intToFloat(int i) { return i * 1.0f; }

int roundToNearestInt(const double& toRound, const int& nearest) { return lround(toRound / nearest) * nearest; }
