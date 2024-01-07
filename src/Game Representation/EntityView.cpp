//
// Created by Qami on 11/23/2023.
//

#include "EntityView.h"
#include "../Logic Library/Stopwatch.h"
#include <cmath>
#include <iostream>

namespace Game {
void EntityView::update(Logic::EntityModel* subject) {}

EntityView::EntityView() : Logic::Observer() {}

PacMan::PacMan()
    : spriteFull({PACMAN_OFFSET_X, PACMAN_OFFSET_Y, PACMAN_SIZE, PACMAN_SIZE}),
      currentMoves({spriteFull, spriteFull, spriteFull}), prevlocation({-60, -60}), location({-60, -60}),
      drawlocation({0, 0}), lastTexture(0), direction(UP), speed(PACMAN_SPEED),
      moves({{{PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (10 * PACMAN_SIZE) + (10 * PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE},
              {PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (11 * PACMAN_SIZE) + (11 * PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE}}

             ,
             {{PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (7 * PACMAN_SIZE) + (7 * PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE},
              {PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (8 * PACMAN_SIZE) + (8 * PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE}}

             ,
             {{PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (4 * PACMAN_SIZE) + (4 * PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE},
              {PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (5 * PACMAN_SIZE) + (5 * PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE}}

             ,
             {{PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (PACMAN_SIZE) + (PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE},
              {PACMAN_OFFSET_X, PACMAN_OFFSET_Y + (2 * PACMAN_SIZE) + (2 * PACMAN_GAP), PACMAN_SIZE, PACMAN_SIZE}}}),
      EntityView() {}

void PacMan::update(Logic::EntityModel* subject) {
    prevlocation = location;
    location = subject->getLocation();
    direction = subject->getDirection();
    drawlocation = {0, 0};
    currentMoves[1] = moves[direction].second;
    currentMoves[2] = moves[direction].first;
}

const position& PacMan::getLocation() const { return location; }

IntRect PacMan::getTexture() {
    int index = lastTexture;
    if (Logic::Stopwatch::getInstance()->totalPassed(PACMAN_ANIMATION_SPEED, lastTextureChange))
        lastTexture = (lastTexture + 1) % 3;
    return currentMoves[index];
}

const position& PacMan::getPrevlocation() const { return prevlocation; }

const directions& PacMan::getDirection() const { return direction; }

float lerp(float a, float b, float t) { return a + t * (b - a); }

void PacMan::draw(RenderWindow& w, const Texture& texture) {
    Sprite pacMan;
    pacMan.setOrigin(17, 17);
    pacMan.setTexture(texture);
    pacMan.setTextureRect(getTexture());

    float startX = 25 + prevlocation.x * SCALE_SIZE;
    float startY = 21 + prevlocation.y * SCALE_SIZE;

    float targetX = 25 + location.x * SCALE_SIZE;
    float targetY = 21 + location.y * SCALE_SIZE;

    float deltaMoveX = intToFloat(possibleDirections[direction].x) * Logic::Stopwatch::getInstance()->calcDeltaTime();
    float deltaMoveY = intToFloat(possibleDirections[direction].y) * Logic::Stopwatch::getInstance()->calcDeltaTime();

    // Linear interpolation
    drawlocation.x += deltaMoveX * SCALE_SIZE;
    drawlocation.y += deltaMoveY * SCALE_SIZE;
    Vector2f nextPosition = {startY + drawlocation.y, startX + drawlocation.x};

    cout << "drawLocationX: " << drawlocation.x << " drawLocationY: " << drawlocation.y << endl;
    cout << "deltaMoveX: " << deltaMoveX << " deltaMoveY: " << deltaMoveY << endl;
    cout << "Final Position: " << startY + drawlocation.y << ", " << startX + drawlocation.x << endl;
    cout << endl;

    pacMan.setPosition(nextPosition);
    w.draw(pacMan);
}

Ghost::Ghost() : EntityView() {}

Ghost::Ghost(int i)
    : speed(GHOST_SPEED), lastTexture(0), lastTextureChange(0), type(SCATTER_GHOST), movementInterval(0),
      color(intToColors(i)), direction(RIGHT), prevlocation({-60, -60}), location({-60, -60}), drawlocation({-60, -60}),
      moves({{{GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP),
               GHOST_OFFSET_Y + (6 * GHOST_SIZE) + (6 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE},
              {GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP),
               GHOST_OFFSET_Y + (7 * GHOST_SIZE) + (7 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE}}

             ,
             {{GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP),
               GHOST_OFFSET_Y + (4 * GHOST_SIZE) + (4 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE},
              {GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP),
               GHOST_OFFSET_Y + (5 * GHOST_SIZE) + (5 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE}}

             ,
             {{GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP),
               GHOST_OFFSET_Y + (2 * GHOST_SIZE) + (2 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE},
              {GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP),
               GHOST_OFFSET_Y + (3 * GHOST_SIZE) + (3 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE}}

             ,
             {{GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP), GHOST_OFFSET_Y, GHOST_SIZE, GHOST_SIZE},
              {GHOST_OFFSET_X + (color * GHOST_SIZE) + (color * GHOST_GAP), GHOST_OFFSET_Y + (GHOST_SIZE) + (GHOST_GAP),
               GHOST_SIZE, GHOST_SIZE}}}),

      movesEaten({{GHOST_OFFSET_X + (6 * GHOST_SIZE) + (6 * GHOST_GAP),
                   GHOST_OFFSET_Y + (8 * GHOST_SIZE) + (8 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE},
                  {GHOST_OFFSET_X + (6 * GHOST_SIZE) + (6 * GHOST_GAP),
                   GHOST_OFFSET_Y + (7 * GHOST_SIZE) + (7 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE},
                  {GHOST_OFFSET_X + (6 * GHOST_SIZE) + (6 * GHOST_GAP),
                   GHOST_OFFSET_Y + (6 * GHOST_SIZE) + (6 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE},
                  {GHOST_OFFSET_X + (6 * GHOST_SIZE) + (6 * GHOST_GAP),
                   GHOST_OFFSET_Y + (5 * GHOST_SIZE) + (5 * GHOST_GAP), GHOST_SIZE, GHOST_SIZE}}),

      spriteFright({{GHOST_OFFSET_X, 554, GHOST_SIZE, GHOST_SIZE},
                    {GHOST_OFFSET_X, 554 + GHOST_SIZE + GHOST_GAP, GHOST_SIZE, GHOST_SIZE}}),
      spriteFrightRunningOut({{GHOST_OFFSET_X + GHOST_SIZE + GHOST_GAP, 554, GHOST_SIZE, GHOST_SIZE},
                              {GHOST_OFFSET_X, 554 + GHOST_SIZE + GHOST_GAP, GHOST_SIZE, GHOST_SIZE}}),
      currentMoves(moves[3]), EntityView() {}

void Ghost::update(Logic::EntityModel* subject) {
    prevlocation = location;
    location = subject->getLocation();
    direction = !subject->getDirection(); // Inverting it to get the facing direction of the Ghost

    switch (subject->getType()) {
    case FRIGHTENED_GHOST:
        currentMoves = (Logic::Stopwatch::getInstance()->isFrightAlmostDue()) ? spriteFrightRunningOut : spriteFright;
        speed = FRIGHTENED_GHOST_SPEED;
        break;
    case EATEN_GHOST:
        currentMoves = {movesEaten[direction], movesEaten[direction]};
        speed = EATEN_GHOST_SPEED;
        break;
    default:
        currentMoves = moves[direction];
        speed = GHOST_SPEED;
        break;
    }

    if (type != subject->getType()) {
        type = subject->getType();
        movementInterval = 0;
    }
}

const position& Ghost::getLocation() const { return location; }

IntRect Ghost::getTexture() {
    if (Logic::Stopwatch::getInstance()->totalPassed(GHOST_SPEED / 1.5, lastTextureChange)) {
        lastTexture++;
    }

    if (lastTexture % 2 == 0) {
        return currentMoves.first;
    } else {
        return currentMoves.second;
    }
}

int& Ghost::getSpeed() { return speed; }

int& Ghost::getMovementInterval() { return movementInterval; }

Coin::Coin() : texture({COIN_OFFSET_X, COIN_OFFSET_Y, COIN_SIZE, COIN_SIZE}), EntityView() {}

void Coin::update(Logic::EntityModel* subject) { EntityView::update(subject); }

const IntRect& Coin::getTexture() const { return texture; }

Fruit::Fruit() : texture({FRUIT_OFFSET_X, FRUIT_OFFSET_Y, FRUIT_SIZE, FRUIT_SIZE}), EntityView() {}

void Fruit::update(Logic::EntityModel* subject) { EntityView::update(subject); }

const IntRect& Fruit::getTexture() const { return texture; }

Wall::Wall() : EntityView() {}

void Wall::update(Logic::EntityModel* subject) { EntityView::update(subject); }

const IntRect& Wall::getTexture() const { return texture; }

void Wall::setTexture(const int index) {
    texture = {WALL_OFFSET + (index * WALL_SIZE) + (index * WALL_GAP), WALL_OFFSET, WALL_SIZE, WALL_SIZE};
}

const IntRect& Door::getTexture() const { return texture; }

Door::Door()
    : texture({WALL_OFFSET + (16 * WALL_SIZE) + (16 * WALL_GAP), WALL_OFFSET, WALL_SIZE, WALL_SIZE}), EntityView() {}

void Door::update(Logic::EntityModel* subject) { EntityView::update(subject); }

} // namespace Game