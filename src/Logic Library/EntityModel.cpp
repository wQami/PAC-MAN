//
// Created by Qami on 11/23/2023.
//

#include <iostream>
#include <algorithm>
#include "EntityModel.h"

namespace Logic {
    EntityModel::EntityModel(EntityModel *pModel) : Subject() {
        type = pModel->type;
        eatable = pModel->eatable;
        value = pModel->value;
    }

    EntityModel::EntityModel() : Subject(){
        type = EMPTY;
        eatable = false;
        value = 0;
    }

    entities EntityModel::getType() const {
        return type;
    }

    void EntityModel::setType(entities entityType) {
        EntityModel::type = entityType;
    }

    bool EntityModel::isEatable() const {
        return eatable;
    }

    void EntityModel::setEatable(bool eatable) {
        EntityModel::eatable = eatable;
    }

    void EntityModel::attach(Observer* &obs) {
        _observers.push_back(obs);
    }

    void EntityModel::detach(Observer* &obs) {
        _observers.erase(remove(_observers.begin(), _observers.end(), obs), _observers.end());
    }

    void EntityModel::notify() {
        for(const auto& obs : _observers){
            obs->update(this);
        }
    }

    int EntityModel::getValue() const {
        return value;
    }

    void EntityModel::setValue(int value) {
        EntityModel::value = value;
    }
} // Logic