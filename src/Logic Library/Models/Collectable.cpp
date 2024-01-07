//
// Created by Qami on 12/2/2023.
//

#include "Collectable.h"

namespace Logic {
Collectable::Collectable() {
    setType(EMPTY);
    setEatable(true);
}

Coin::Coin() {
    setValue(10);
    setType(COIN);
}

void Coin::notify() { Logic::EntityModel::notify(); }

Fruit::Fruit() {
    setValue(100);
    setType(FRUIT);
}

void Fruit::notify() { EntityModel::notify(); }
} // namespace Logic