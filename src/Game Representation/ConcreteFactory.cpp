//
// Created by Qami on 11/23/2023.
//

#include "ConcreteFactory.h"
#include <iostream>

namespace Game {

void SingleViewFactory::transferShared(shared_ptr<PacMan>& p, vector<shared_ptr<Ghost>>& g, shared_ptr<Coin>& c,
                                       shared_ptr<Fruit>& f, shared_ptr<Wall>& w, shared_ptr<Door>& d) {
    p = sharedPacManView;
    g = sharedGhostViews;
    c = sharedCoinView;
    f = sharedFruitView;
    w = sharedWallView;
    d = sharedDoorView;
}

shared_ptr<Game::PacMan> ViewFactory::createPacmanView() { return make_shared<PacMan>(); }

shared_ptr<Ghost> ViewFactory::createGhostView() { return make_shared<Ghost>(); }

shared_ptr<Ghost> ViewFactory::createGhostView(int i) { return make_shared<Ghost>(Ghost(i)); }

shared_ptr<Coin> ViewFactory::createCoinView() { return make_shared<Coin>(); }

shared_ptr<Fruit> ViewFactory::createFruitView() { return make_shared<Fruit>(); }

shared_ptr<Wall> ViewFactory::createWallView() { return make_shared<Wall>(); }

shared_ptr<Door> ViewFactory::createDoorView() { return make_shared<Door>(); }

void ViewFactory::viewFactory(const Logic::sharedEntityModel& em) {
    shared_ptr<Logic::Observer> created;
    switch (em->getType()) {
    case PACMAN:
    case LOSER_PACMAN:
    case WINNER_PACMAN:
        created = createPacmanView();
        break;
    case GHOST:
    case FRIGHTENED_GHOST:
    case SCATTER_GHOST:
    case EATEN_GHOST:
        created = createGhostView();
        break;
    case COIN:
        created = createCoinView();
        break;
    case FRUIT:
        created = createFruitView();
        break;
    case WALL:
        created = createWallView();
        break;
    case DOOR:
        created = createDoorView();
        break;
    case EMPTY:
        break;
    }
    em->attach(created);
}

shared_ptr<Logic::PacMan> ViewFactory::createPacman() { return nullptr; }

shared_ptr<Logic::Ghost> ViewFactory::createGhost() { return nullptr; }

shared_ptr<Logic::Ghost> ViewFactory::createGhost(int i) { return nullptr; }

shared_ptr<Logic::Coin> ViewFactory::createCoin() { return nullptr; }

shared_ptr<Logic::Fruit> ViewFactory::createFruit() { return nullptr; }

shared_ptr<Logic::Wall> ViewFactory::createWall() { return nullptr; }

shared_ptr<Logic::Door> ViewFactory::createDoor() { return nullptr; }

Logic::sharedEntityModel ViewFactory::modelFactory(char c) { return nullptr; }

void SingleViewFactory::viewFactory(const Logic::sharedEntityModel& em) {
    shared_ptr<Logic::Observer> created;
    switch (em->getType()) {
    case PACMAN:
    case LOSER_PACMAN:
    case WINNER_PACMAN:
        if (!sharedPacManView)
            sharedPacManView = ViewFactory::createPacmanView();
        created = sharedPacManView;
        break;
    case GHOST:
    case FRIGHTENED_GHOST:
    case SCATTER_GHOST:
    case EATEN_GHOST:
        sharedGhostViews.push_back(ViewFactory::createGhostView(sharedGhostViews.size() % 4));
        created = sharedGhostViews.back();
        break;
    case COIN:
        if (!sharedCoinView)
            sharedCoinView = ViewFactory::createCoinView();
        created = sharedCoinView;
        break;
    case FRUIT:
        if (!sharedFruitView)
            sharedFruitView = ViewFactory::createFruitView();
        created = sharedFruitView;
        break;
    case WALL:
        if (!sharedWallView)
            sharedWallView = ViewFactory::createWallView();
        created = sharedWallView;
        break;
    case DOOR:
        if (!sharedDoorView)
            sharedDoorView = ViewFactory::createDoorView();
        created = sharedDoorView;
        break;
    case EMPTY:
        break;
    }
    em->attach(created);
}

void SingleViewFactory::transferShared(shared_ptr<Logic::PacMan>& p, vector<shared_ptr<Logic::Ghost>>& g,
                                       shared_ptr<Logic::Coin>& c, shared_ptr<Logic::Fruit>& f,
                                       shared_ptr<Logic::Wall>& w, shared_ptr<Logic::Door>& d) {}
} // namespace Game