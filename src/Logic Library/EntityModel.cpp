//
// Created by Qami on 11/23/2023.
//

#include <iostream>
#include <algorithm>
#include "EntityModel.h"

namespace Logic {
    EntityModel::EntityModel(EntityModel *pModel) : type(pModel->type), eatable(pModel->eatable), value(pModel->value),
                                                    location(pModel->location), direction(UP), Subject() {
    }

    EntityModel::EntityModel() : type(EMPTY), eatable(false), value(0), location({0, 0}), direction(UP), Subject() {
    }

    entities EntityModel::getType() const {
        return type;
    }

    void EntityModel::setType(entities entityType) {
        EntityModel::type = entityType;

        switch (entityType) {
            case PACMAN:
                setEatable(true);
                value = 0;
                break;
            case GHOST:
            case SCATTER_GHOST:
                value = 0;
                eatable = false;
                break;
            case FRIGHTENED_GHOST:
                value = 400;
                eatable = true;
                break;
            case EATEN_GHOST:
                notify();
                value = 0;
                break;
            case COIN:
                value = 10;
                eatable = true;
                break;
            case FRUIT:
                value = 100;
                eatable = true;
                break;
            case LOSER_PACMAN:
            case WINNER_PACMAN:
                notify();
                break;
            case WALL:
            case DOOR:
            case EMPTY:
                break;
        }
    }

    bool EntityModel::isEatable() const {
        return eatable;
    }

    void EntityModel::setEatable(bool eatable) {
        EntityModel::eatable = eatable;
    }

    void EntityModel::attach(shared_ptr<Observer> &obs) {
        _observers.push_back(obs);
    }

    void EntityModel::detach(shared_ptr<Observer> &obs) {
        _observers.erase(remove(_observers.begin(), _observers.end(), obs), _observers.end());
    }

    void EntityModel::notify() {
        for (const auto &obs: _observers) {
            obs->update(this);
        }
    }

    int EntityModel::getValue() const {
        return value;
    }

    void EntityModel::setValue(int value) {
        EntityModel::value = value;
    }

    const position &EntityModel::getLocation() const {
        return location;
    }

    directions EntityModel::getDirection() const {
        return direction;
    }

    void EntityModel::setLocation(position p) {
        location = p;
    }

    void EntityModel::setDirection(directions d) {
        direction = d;
    }
} // Logic