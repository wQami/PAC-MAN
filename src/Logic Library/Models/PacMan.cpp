//
// Created by Qami on 12/2/2023.
//

#include "PacMan.h"
#include "../Stopwatch.h"
#include <cmath>
#include <iostream>

namespace Logic {
PacMan::PacMan() { setType(PACMAN); }

const position& PacMan::getStartLocation() const { return startLocation; }

const position& PacMan::getLocation() const { return EntityModel::getLocation(); }

directions PacMan::getDirection() const { return EntityModel::getDirection(); }

void PacMan::setLocation(const position& location) {
    EntityModel::setLocation(location);
    PacMan::startLocation = location;
    EntityModel::notify();
}

void PacMan::move(directions e) {
    setDirection(e);
    position location = getLocation();
    location.x += possibleDirections[e].x;
    location.y += possibleDirections[e].y;
    EntityModel::setLocation(location);
    EntityModel::notify();
}

void PacMan::hit() {
    setValue(1);
    EntityModel::notify();
    setValue(0);
}

void PacMan::resetPosition() {
    setLocation(startLocation);
    EntityModel::notify();
}
} // namespace Logic