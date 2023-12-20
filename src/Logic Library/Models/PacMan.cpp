//
// Created by Qami on 12/2/2023.
//

#include "PacMan.h"

namespace Logic {
    PacMan::PacMan() {
        setValue(3);
        setType(PACMAN);
    }

    const pair<int, int> &PacMan::getStartLocation() const {
        return startLocation;
    }

    const pair<int, int> &PacMan::getLocation() const {
        return location;
    }

    void PacMan::setLocation(const pair<int, int> &location) {
        PacMan::location = location;
        PacMan::startLocation = location;
    }

    void PacMan::move(events e) {
        switch (e) {
            case MOVE_UP:
                location.first-=1;
                break;
            case MOVE_DOWN:
                location.first+=1;
                break;
            case MOVE_LEFT:
                location.second-=1;
                break;
            case MOVE_RIGHT:
                location.second+=1;
                break;
            default:
                break;
        }
    }

    void PacMan::hit() {
        if(getValue() != 0){
            setValue(getValue()-1);
        }
    }
} // Logic