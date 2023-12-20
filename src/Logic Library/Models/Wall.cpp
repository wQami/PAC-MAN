//
// Created by Qami on 12/2/2023.
//

#include <iostream>
#include "Wall.h"

namespace Logic {
    Wall::Wall(){
        setType(WALL);
    }

    Door::Door() {
        setType(DOOR);
        isOpen = false;
    }

    void Door::open(){
        isOpen = true;
    }

    void Door::close(){
        isOpen = false;
    }
} // Logic