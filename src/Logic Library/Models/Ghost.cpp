//
// Created by Qami on 12/2/2023.
//

#include "Ghost.h"

namespace Logic {
    Ghost::Ghost() {
        color = red;
        setType(GHOST);
        setValue(400);
    }

    Ghost::Ghost(colors c) {
        color = c;
        setType(GHOST);
        setValue(400);
    }

    colors Ghost::getColor() const {
        return color;
    }

    void Ghost::setColor(colors c) {
        Ghost::color = c;
    }

    const pair<int, int> &Ghost::getStartLocation() const {
        return startLocation;
    }

    const pair<int, int> &Ghost::getLocation() const {
        return location;
    }

    void Ghost::setLocation(const pair<int, int> &location) {
        Ghost::location = location;
        Ghost::startLocation = location;

    }
} // Logic