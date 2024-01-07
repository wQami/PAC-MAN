//
// Created by Qami on 12/2/2023.
//

#include "Ghost.h"
#include "../Random.h"
#include "../Stopwatch.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

namespace Logic {
Ghost::Ghost() : startRound(false), level(1), outOfCage(false), color(red), modeIndex(0) {
    setType(SCATTER_GHOST);
    setDirection(LEFT);
}

Ghost::Ghost(int i) : startRound(false), level(1), outOfCage(false), color(intToColors(i)), modeIndex(0) {
    setType(SCATTER_GHOST);
    setDirection(LEFT);
}

colors Ghost::getColor() const { return color; }

const position& Ghost::getLocation() const { return EntityModel::getLocation(); }

const position& Ghost::getStartLocation() const { return startLocation; }

const sharedEntityModel& Ghost::getUnderGhost() const { return underGhost; }

void Ghost::setLocation(const position& location) {
    setDirection(LEFT);
    EntityModel::setLocation(location);
    Ghost::startLocation = location;
    EntityModel::notify();
}

void Ghost::setLevel(const int& l) { Ghost::level = l; }

void Ghost::setScatterTarget(const position& sT) { Ghost::scatterTarget = sT; }

void Ghost::setUnderGhost(const sharedEntityModel& uG) {

    // Is geen geest en geen pacman of is leeg?
    bool isNotGhostOrPacman = !(uG) || find(ghostTypes.begin(), ghostTypes.end(), uG->getType()) == ghostTypes.end() &&
                                           uG->getType() != PACMAN && uG->getType() != DOOR;
    Ghost::underGhost = (isNotGhostOrPacman) ? uG : nullptr;
}

bool Ghost::isOutOfCage() const { return outOfCage; }

void Ghost::move(directions d) {
    setDirection(!d);
    position location = getLocation();
    location.x += possibleDirections[d].x;
    location.y += possibleDirections[d].y;
    EntityModel::setLocation(location);
    EntityModel::notify();
}

void Ghost::gotOutOfCage() { outOfCage = true; }

void Ghost::backInCage() { outOfCage = false; }

directions Ghost::movement(tilemap& tilemap, const shared_ptr<PacMan>& pacMan, const position& blinky) {
    position target{};
    Random* rng;
    directions direction;
    entities preEatenType;
    changeMode();

    switch (getType()) {
    case GHOST:
        target = targetLocation(pacMan->getLocation(), pacMan->getDirection(), blinky);
        break;
    case SCATTER_GHOST:
        target = scatterTarget;
        break;
    case FRIGHTENED_GHOST:
        rng = Random::getInstance();
        direction = intToDirections(rng->receiveRandom(0, 3));
        return calculateFright(tilemap, direction);
    case EATEN_GHOST:
        backInCage();
        target = startLocation;
        preEatenType = (modeIndex % 2 == 0) ? SCATTER_GHOST : GHOST;
        if (getLocation() == startLocation)
            setType(preEatenType);
        break;
    default:
        target = pacMan->getLocation();
        break;
    }
    return decideDirection(tilemap, target);
}

position Ghost::targetLocation(const position& target, const directions& pacManDirection, const position& blinky) {
    position targetingPosition = target;
    directions direction = pacManDirection;
    switch (color) {
    case red:
        break;
    case pink:
        targetingPosition.x += possibleDirections[direction].x * 4;
        targetingPosition.y += possibleDirections[direction].y * 4;
        break;
    case blue:
        targetingPosition.x += possibleDirections[direction].x * 2;
        targetingPosition.y += possibleDirections[direction].y * 2;

        targetingPosition.x += -(targetingPosition.x - blinky.x);
        targetingPosition.y += -(targetingPosition.y - blinky.y);
        break;
    case orange:
        double distance =
            pow((targetingPosition.x - getLocation().x), 2) + pow((targetingPosition.y - getLocation().y), 2);
        if (distance <= 8) {
            targetingPosition = scatterTarget;
        }
        break;
    }
    return targetingPosition;
}

directions Ghost::decideDirection(tilemap& tilemap, const position& targetLocation) const {
    directions direction = UP;
    double minimal = numeric_limits<double>::infinity();
    vector<bool> surroundingTypes = {false, false, false, false};

    for (int i = 0; i < possibleDirections.size(); i++) {
        int pX = possibleDirections[i].x;
        int pY = possibleDirections[i].y;
        position nextL = {getLocation().x + pX, getLocation().y + pY};
        double distance = pow(targetLocation.x - nextL.x, 2) + pow(targetLocation.y - nextL.y, 2);
        entities nextType = (tilemap[nextL.x][nextL.y]) ? tilemap[nextL.x][nextL.y]->getType() : EMPTY;
        surroundingTypes[i] =
            nextType == EMPTY || (nextType == DOOR && !isOutOfCage()) || tilemap[nextL.x][nextL.y]->isEatable();

        if (i == getDirection() || nextType == WALL || nextType == GHOST || nextType == SCATTER_GHOST ||
            (nextType == DOOR && isOutOfCage())) {
            continue;
        } else {
            if (distance < minimal) {
                minimal = distance;
                direction = intToDirections(i);
            }
        }
    }

    if (count(surroundingTypes.begin(), surroundingTypes.end(), true) == 1) {
        auto it = find(surroundingTypes.begin(), surroundingTypes.end(), true);
        direction = intToDirections(it - surroundingTypes.begin());
    }

    return direction;
}

// First with recursive funtion --> stack Overflow error (Windows).

directions Ghost::calculateFright(tilemap& tilemap, directions d) const {
    directions original = d;
    while (true) {
        position nextMove = possibleDirections[d];
        position nextL = {getLocation().x + nextMove.x, getLocation().y + nextMove.y};
        entities nextType = (tilemap[nextL.x][nextL.y]) ? tilemap[nextL.x][nextL.y]->getType() : EMPTY;

        if (!(d == getDirection() || nextType == WALL || nextType == GHOST || nextType == SCATTER_GHOST ||
              (nextType == DOOR && isOutOfCage()))) {
            return d;
        }
        d = (d == 0) ? intToDirections(3) : intToDirections(d - 1);
        if (d == original) {
            break;
        };
    }
    return d;
}

void Ghost::resetPosition() {
    EntityModel::setLocation(startLocation);
    outOfCage = false;
    startRound = false;
    underGhost = nullptr;
    setType(SCATTER_GHOST);
    if (modeIndex % 2 != 0 && modeIndex - 1 >= 0)
        modeIndex--;
    EntityModel::notify();
}

void Ghost::changeMode() {
    if (getType() == FRIGHTENED_GHOST) {
        unsigned long long frightIndex = (level <= DURATION_FRIGHT.size()) ? level : DURATION_FRIGHT.size() - 1;
        Stopwatch::getInstance()->frightLeft(DURATION_FRIGHT[frightIndex]);
        if (Stopwatch::getInstance()->secondsPassed(DURATION_FRIGHT[frightIndex])) {
            entities type = (modeIndex % 2 == 0) ? SCATTER_GHOST : GHOST;
            setType(type);
        }

    } else if (Stopwatch::getInstance()->secondsPassed(modeTimings[intToTiming(level)][modeIndex]) &&
               modeIndex < modeTimings[intToTiming(level)].size() - 1) {
        modeIndex++;

        if (getType() == GHOST && modeIndex % 2 == 0) {
            setType(SCATTER_GHOST);
        } else if (getType() == SCATTER_GHOST && modeIndex % 2 != 0) {
            setType(GHOST);
        }
    }
}

void Ghost::frighten() {
    if (getType() != EATEN_GHOST) {
        setType(FRIGHTENED_GHOST);
        EntityModel::notify();
    }
}

bool Ghost::hasStarted() const { return startRound; }

void Ghost::roundStart() { startRound = true; }

void Ghost::roundWaitTurn() { startRound = false; }

} // namespace Logic