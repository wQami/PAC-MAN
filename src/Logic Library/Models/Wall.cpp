//
// Created by Qami on 12/2/2023.
//

#include "Wall.h"
#include "../Stopwatch.h"
#include <iostream>

namespace Logic {
Wall::Wall() { setType(WALL); }

Door::Door() {
    setType(DOOR);
    setValue(0);
}

void Door::open() { setValue(1); }

void Door::close() { setValue(0); }

bool Door::isClosed() { return getValue() == 0; }

bool Door::itsTime() { return Stopwatch::getInstance()->secondsPassed(DURATION_OPEN_DOOR / 1000); }

} // namespace Logic