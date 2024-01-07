//
// Created by Qami on 11/23/2023.
//

#include "AbstractFactory.h"
#include <iostream>

namespace Logic {
shared_ptr<PacMan> ModelFactory::createPacman() { return make_shared<PacMan>(); }

shared_ptr<Ghost> ModelFactory::createGhost() { return make_shared<Ghost>(); }

shared_ptr<Ghost> ModelFactory::createGhost(int i) { return make_shared<Ghost>(Ghost(i)); }

shared_ptr<Coin> ModelFactory::createCoin() { return make_shared<Coin>(); }

shared_ptr<Fruit> ModelFactory::createFruit() { return make_shared<Fruit>(); }

shared_ptr<Wall> ModelFactory::createWall() { return make_shared<Wall>(); }

shared_ptr<Door> ModelFactory::createDoor() { return make_shared<Door>(); }

sharedEntityModel ModelFactory::modelFactory(char c) {
    sharedEntityModel created;
    switch (c) {
    case 'x':
        return createWall();
    case 'O':
        return createPacman();
    case 'y':
        return createFruit();
    case 'g':
        return createGhost();
    case 'b':
    case ' ':
        return nullptr;
    case '-':
        return createCoin();
    case '=':
        return createDoor();
    default:
        cout << "Wrong input, character gets skipped. Input: " << c << endl;
        return nullptr;
    }
}

sharedEntityModel SingleModelFactory::modelFactory(char c) {
    sharedEntityModel created;
    switch (c) {
    case 'x':
        if (!sharedWall) {
            sharedWall = ModelFactory::createWall();
        }
        created = sharedWall;
        break;

    case 'O':
        if (!sharedPacMan) {
            sharedPacMan = ModelFactory::createPacman();
        }
        created = sharedPacMan;
        break;

    case 'y':
        if (!sharedFruit) {
            sharedFruit = ModelFactory::createFruit();
        }
        created = sharedFruit;
        break;

    case 'g':
        sharedGhosts.push_back(ModelFactory::createGhost(sharedGhosts.size() % 4));
        created = sharedGhosts.back();
        break;

    case 'b':
    case ' ':
        created = nullptr;
        break;

    case '-':
        if (!sharedCoin) {
            sharedCoin = ModelFactory::createCoin();
        }
        created = sharedCoin;
        break;

    case '=':
        if (!sharedDoor) {
            sharedDoor = ModelFactory::createDoor();
        }
        created = sharedDoor;
        break;

    default:
        cout << "Wrong input, character gets skipped. Input: " << c << endl;
        created = nullptr;
        break;
    }
    return created;
}

void SingleModelFactory::transferShared(shared_ptr<PacMan>& p, vector<shared_ptr<Ghost>>& g, shared_ptr<Coin>& c,
                                        shared_ptr<Fruit>& f, shared_ptr<Wall>& w, shared_ptr<Door>& d) {
    p = std::move(sharedPacMan);
    g = std::move(sharedGhosts);
    c = std::move(sharedCoin);
    f = std::move(sharedFruit);
    w = std::move(sharedWall);
    d = std::move(sharedDoor);
}

shared_ptr<Game::PacMan> ModelFactory::createPacmanView() { return nullptr; }

shared_ptr<Game::Ghost> ModelFactory::createGhostView() { return nullptr; }

shared_ptr<Game::Ghost> ModelFactory::createGhostView(int i) { return nullptr; }

shared_ptr<Game::Coin> ModelFactory::createCoinView() { return nullptr; }

shared_ptr<Game::Fruit> ModelFactory::createFruitView() { return nullptr; }

shared_ptr<Game::Wall> ModelFactory::createWallView() { return nullptr; }

shared_ptr<Game::Door> ModelFactory::createDoorView() { return nullptr; }

void ModelFactory::viewFactory(const sharedEntityModel& em) {}

void SingleModelFactory::transferShared(shared_ptr<Game::PacMan>& p, vector<shared_ptr<Game::Ghost>>& g,
                                        shared_ptr<Game::Coin>& c, shared_ptr<Game::Fruit>& f,
                                        shared_ptr<Game::Wall>& w, shared_ptr<Game::Door>& d) {}
} // namespace Logic